/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInstance.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcotza <dcotza@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 01:46:40 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/14 23:03:06 by dcotza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ServerInstance.hpp"
#include "../includes/Response.hpp"

#include "../includes/utils.hpp"
#include <fcntl.h>
#include <locale>

std::list<int> ServerInstance::server_fds;

ServerInstance::ServerInstance()
{
	
}

ServerInstance::ServerInstance(server_node *server_node, int epoll_fd)
{
	server_nodes.push_back(server_node);
	this->host = server_node->host;
	this->port = server_node->port;
	this->ip = server_node->host_digit;
	this->server_epoll_fd = epoll_fd;
}

void ServerInstance::add_server_node(server_node *server_node)
{
	server_nodes.push_back(server_node);
}

void ServerInstance::start_server()
{
	if (open_socket(ip, port) == -1)
		throw std::runtime_error("Error opening socket");
	if (bind_socket(ip, port) == -1)
		throw std::runtime_error("Error binding socket");
	if (listen(this->server_fd, 10) == -1)
		throw std::runtime_error("Error listening on socket");
	//set non-blocking
	if (fcntl(this->server_fd, F_SETFL, O_NONBLOCK, FD_CLOEXEC) == -1)
		throw std::runtime_error("Error setting non-blocking socket");
	printf("adding server_fd = %d  to interest\n", server_fd);
	
	server_ev = new epoll_event;
	server_ev->events = EPOLLIN | EPOLLET;
	server_ev->data.fd = server_fd;
	/* Allow epoll to monitor the server_fd socket */
	if (epoll_ctl(server_epoll_fd, EPOLL_CTL_ADD, server_fd, server_ev) == -1) {
	    perror ("epoll_ctl");
	    exit(EXIT_FAILURE);
	}
	std::cout << "Server started on " << this->host << ":" << this->port << std::endl;
	this->server_fds.push_back(server_fd);
}

void ServerInstance::accept_client()
{
	ClientInstance client(server_fd, server_epoll_fd);
	printf("accepted client_fd = %d\n", client.get_fd());
	clients.push_back(client);
}

void ServerInstance::disconnect_client(ClientInstance *client)
{
	std::cout << "Disconnecting client" << std::endl;
	if (epoll_ctl(server_epoll_fd, EPOLL_CTL_DEL, client->get_fd(), NULL) == -1)
	{
		perror("epoll_ctl");
	}
	close(client->get_fd());
	clients.remove(*client);
}

void ServerInstance::handle_request(ClientInstance *client)
{
	std::cout << "Handling request" << std::endl;
	if (client->read_request() == 0)
	{
		disconnect_client(client);
		return ;
	}
	Response response = Response(client->request, this);
	response.send_response(client->get_fd());
	delete client->request;
	std::cout << "Request handled" << std::endl;
}

void ServerInstance::handle_client(int client_fd)
{
	for (std::list<ClientInstance>::iterator client = clients.begin(); client != clients.end(); ++client)
	{
		if (client->get_fd() == client_fd)
		{
			handle_request(&(*client));
			break ;
		}
	}
}

ServerInstance::~ServerInstance()
{	
}

int	ServerInstance::open_socket(uint32_t ip, int port)
{
	this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->server_fd == 0)
		return (-1);
	int opt = 1;
	if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
		return (-1);
	return (0);
}

void	set_server_address(sockaddr_in &address, uint32_t ip, int port)
{
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(ip);
	address.sin_port = htons(port);
}

int ServerInstance::bind_socket(uint32_t ip, int port)
{
	struct sockaddr_in address;
	set_server_address(address, ip, port);
	if (bind(this->server_fd, (struct sockaddr *)&address, sizeof(address)) == -1)
		return (-1);
	return (0);
}

int ServerInstance::get_server_fd()
{
	return (this->server_fd);
}

bool ServerInstance::is_client(int fd)
{
	for (std::list<ClientInstance>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->get_fd() == fd)
			return (true);
	}
	return (false);
}

server_node *ServerInstance::get_server_node(std::string host)
{
	for (std::list<server_node *>::iterator it = server_nodes.begin(); it != server_nodes.end(); ++it)
	{
		//check if host is in server_names
		for (std::list<std::string>::iterator it2 = (*it)->server_names.begin(); it2 != (*it)->server_names.end(); ++it2)
		{
			if (*it2 == host)
				return (*it);
		}
	}
	return (*server_nodes.begin());
}

location_node *ServerInstance::get_location_node(server_node *server_node, std::string dir_path)
{
	if (dir_path.c_str() != NULL && dir_path != "/" && dir_path[dir_path.length() - 1] == '/')
		dir_path = dir_path.substr(0, dir_path.length() - 1);
	for (std::list<location_node >::iterator it = server_node->locations.begin(); it != server_node->locations.end(); ++it)
	{	
		printf("location path = %s\n", it->path.c_str());
		printf("dir path = %s\n", dir_path.c_str());
		if (it->path == dir_path)
			return (&(*it));
		//use std::mismatch to compare strings
		std::pair<std::string::iterator, std::string::iterator> res = std::mismatch(it->path.begin(), it->path.end(), dir_path.begin());
		if (res.first == it->path.end() && it->path != "/")
			return (&(*it));
	}
	return (NULL);
}