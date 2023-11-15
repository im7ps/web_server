/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientInstance.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:01:20 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/14 22:56:58 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ClientInstance.hpp"
#include "../includes/Response.hpp"
#include "../includes/CGI.hpp"
#include <fcntl.h>

ClientInstance::ClientInstance(int server_fd, int epoll_fd)
{
	socklen_t	client_address_len = sizeof(client_address);

	client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_address_len);

/*     timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    if (setsockopt(client_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
	{
        perror("Errore nell'impostare il timeout");
		close(client_fd);
        exit(EXIT_FAILURE);
    } */

	setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, NULL, 0);
	if (client_fd < 0)
	{
		//TODO handle error
		close(client_fd);
		std::cout << "Error accepting connection" << std::endl;
	}
	epoll_event *server_ev = new epoll_event;
	server_ev->data.fd = client_fd;
	server_ev->events = EPOLLIN | EPOLLET;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, server_ev) == -1) {
	    // perror ("epoll_ctl");
	    // exit(EXIT_FAILURE);
		std::cout << "Error adding client_fd to epoll" << std::endl;
	}
}
// {
// 	socklen_t	client_address_len = sizeof(client_address);

// 	client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_address_len);
// 	if (client_fd < 0)
// 	{
// 		//TODO handle error
// 		std::cout << "Error accepting connection" << std::endl;
// 	}
// }

int ClientInstance::read_request()
{
	char buffer[1024] = {0};
	std::cout << "Reading request" << std::endl;
	int cumolative_valread = 0;
	
	int valread = recv(client_fd, buffer, 1024, 0);

	cumolative_valread += valread;
	if (valread == 0)
		return cumolative_valread;
	while (valread > 0)
	{
		raw_request += std::string(buffer);
		if (valread < 1024)
		{
			break ;
		}
		valread = recv(client_fd, buffer, 1024, 0);
		cumolative_valread += valread;
	}
	if (valread == -1)
	{
		//TODO handling error
		std::cout << "Error reading request" << std::endl;
	}

	std::cout << "\n\nRaw request: " << raw_request << "\nEnd raw request" << std::endl;

 	request = new Request(raw_request);
	std::cout << "\n\nBody " << request->body << std::endl;


/*	
	da inserire per le richieste POST un modo per passare il body alla cgi e 
	CGI cgi;
	cgi.exec_cgi(*request); */

	raw_request.clear();
	std::cout << "Request read\n" << std::endl;
	return cumolative_valread;
}
//define operator 
bool ClientInstance::operator==(const ClientInstance &other)
{
	if (this->client_fd == other.client_fd)
		return true;
	return false;
}
int ClientInstance::get_fd()
{
	return (this->client_fd);
}

ClientInstance::~ClientInstance()
{
}