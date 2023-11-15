/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInstance.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 01:47:26 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/14 03:02:22 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_INSTANCE_HPP
# define SERVER_INSTANCE_HPP

#include "ServerConfig.hpp"
#include "ClientInstance.hpp"
#include <sys/socket.h>
#include <sys/epoll.h>
#include "Request.hpp"

#define SERVER_NAME "webserv"
#define SERVER_VERSION "1.0"


//serverNode name sucks
class ServerInstance
{
private:
	std::string					host;
	int							port;
	uint32_t					ip;
	std::list<server_node *>	server_nodes;
	int 						server_fd;
	int							server_epoll_fd;
	epoll_event					*server_ev;
	std::list<ClientInstance>	clients;
	
	int			open_socket(uint32_t ip, int port);
	int			bind_socket(uint32_t ip, int port);

public:
	static std::list<int>		server_fds;
	void 			add_server_node(server_node *server_node);
	void 			start_server();
	void 			accept_client();
	void 			disconnect_client(ClientInstance *client_instance);
	void 			handle_client(int client_fd);
	int				get_server_fd();
	bool 			is_client(int fd);
	server_node		*get_server_node(std::string host);
	location_node	*get_location_node(server_node *server_node, std::string path);

	void	handle_request(ClientInstance *client_instance);


	ServerInstance(server_node *server_node, int epoll_fd);
	ServerInstance();
	~ServerInstance();
};

#endif