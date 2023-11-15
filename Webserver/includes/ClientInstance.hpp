/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientInstance.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:01:30 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/14 02:50:30 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP
# include <sys/socket.h>
# include <sys/epoll.h>
# include <unistd.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string>
# include <iostream>

#include "../includes/Request.hpp"

class ClientInstance
{
private:
	sockaddr_in		client_address;
	int				client_fd;
	std::string		raw_request;
public:
	Request			*request;
	long long		start_time;
	ClientInstance(int server_fd, int epoll_fd);
	~ClientInstance();
	bool operator == ( const ClientInstance& rhs );


	// ClientInstance&	operator==(const ClientInstance &client_instance);
	
	int		read_request();
	int		get_fd();
};



#endif