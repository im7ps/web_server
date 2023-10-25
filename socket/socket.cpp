/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:57:40 by stepis            #+#    #+#             */
/*   Updated: 2023/10/19 17:13:30 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

static void	socket_listen(int server_id)
{
	if (listen(server_id, 3) < 0)
	{
		throw std::runtime_error("Modalità ascolto fallita\n");
	}
}

static void	socket_bind(int server_id, sockaddr_in& address)
{
	if (bind(server_id, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		throw std::runtime_error("Associazione del socket fallita\n");
	}
}

static void	set_server_address(sockaddr_in& address, int port)
{
	std::cout << "port: " << port << std::endl;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
}

static int	socket_open(int& server_fd)
{
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		throw std::runtime_error("Creazione del socket fallita");
	}
	return (0);
}

static void	create_epoll(int& epoll_fd)
{
	if ((epoll_fd = epoll_create1(0)) == -1)
	{
		throw std::runtime_error("Creazione di epoll fallita");
	}
}

static void	socket_bind_to_epoll(int server_fd, int epoll_fd, epoll_event& event)
{
	event.events = EPOLLIN | EPOLLET;
	event.data.fd = server_fd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1)
	{
		throw std::runtime_error("Errore nell'aggiungere il socket di ascolto a epoll");
	}
}

void parseHttpRequest(const char* buffer, std::string& method, std::string& uri, std::map<std::string, std::string>& headers) {
    std::istringstream requestStream(buffer);
    std::string requestLine;
    std::getline(requestStream, requestLine);
    std::istringstream requestLineStream(requestLine);

    requestLineStream >> method >> uri;

    std::string headerLine;
    while (std::getline(requestStream, headerLine) && !headerLine.empty()) {
        size_t colonPos = headerLine.find(':');
        if (colonPos != std::string::npos) {
            std::string headerName = headerLine.substr(0, colonPos);
            std::string headerValue = headerLine.substr(colonPos + 1);
            headers[headerName] = headerValue;
        }
    }
}

void printHeaders(const std::map<std::string, std::string>& headers) {
    std::map<std::string, std::string>::const_iterator it;
    for (it = headers.begin(); it != headers.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
}

void	socket_handler(ConfigData& configMap)
{
	int server_fd;
	int	epoll_fd;
	struct sockaddr_in address;
	struct epoll_event event, events[MAX_EVENTS];
	
	socket_open(server_fd);
	std::cout << "listen:" << configMap.serverList.begin()->listen << std::endl;
	set_server_address(address, ft_atoi(configMap.serverList.begin()->listen));
	socket_bind(server_fd, address);
	socket_listen(server_fd);
	create_epoll(epoll_fd);
	socket_bind_to_epoll(server_fd, epoll_fd, event);
	
	//questa parte del programma verrà spostata in una dedicata alla gestione delle richieste in arrivo
	while (1)
	{
		int events_num = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
		int	i = -1;
		int	socket;
        std::string method;
        std::string uri;
        std::map<std::string, std::string> headers;
		while (++i < events_num)
		{
			//caso nuova connessione
			if (events[i].data.fd == server_fd)
			{
				//creazione nuova socket
				socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&address);
				//definizione della nuova socket come non bloccante grazie a EPOLLET
				event.events = EPOLLIN | EPOLLET;
				//registrazione dell identificatore della socket associata all evento
				event.data.fd = socket;
				//effettivo collegamento fra la nuova socket e l'istanza epoll
				epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket, &event);
			}
			//gestione comunicazione con il client con una socket già esistente
			else
			{
				//allocazione buffer per la ricezione dei dati
				std::cout << "body_size: " << configMap.serverList.begin()->max_client_body_size << std::endl;
				char tmp_buffer[ft_atoi(configMap.serverList.begin()->max_client_body_size)];
                //std::string buffer;
                int bytes_received;

				//ricezione dati dal client, la size viene salvata in bytes_received
				bytes_received = recv(events[i].data.fd, tmp_buffer, sizeof(tmp_buffer), 0);
                //se abbiamo ricevuto dei dati gestiamo la richiesta
				if (bytes_received > 0)
				{
                    parseHttpRequest(tmp_buffer, method, uri, headers);
					std::cout << "Type: " << method << std::endl;
                    std::cout << "URI:  " << uri << std::endl;
                    //printHeaders(headers);
                    std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello, World";
					//invio della risposta al client
					send(events[i].data.fd, response.c_str(), response.length(), 0);
					close(events[i].data.fd); // Chiudi la connessione dopo la risposta
				}
			}
		}
	}
	
	close(server_fd);
	
}