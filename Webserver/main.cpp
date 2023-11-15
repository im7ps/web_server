/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:27:35 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/14 18:30:47 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/ServerInstance.hpp"
# include "includes/MIME_type_detector.hpp"

//TODO: count unique servers to define MAX_EVENTS
# define MAX_EVENTS 10
int main(int argc, char const *argv[])
{
	long long startTime;

	if (argc != 2) {
		std::cout << "Usage: ./webserv <config_file_path>" << std::endl;
		return (1);
	}
	MIME_type_detector mime_type_detector("utils/mime_types.csv");
	
	ServerConfig server_config((char *)argv[1]);
	struct epoll_event ev, events[MAX_EVENTS];

	/* Create epoll instance */
	int efd = epoll_create(MAX_EVENTS);
	if (efd == -1) {
	    perror ("epoll_create");
	    exit(EXIT_FAILURE);
	}
	// server_config.print_server_nodes(true);
	server_config.print_location_nodes(&server_config.server_nodes.front());
	ServerInstance serverInstance(&server_config.server_nodes.front(), efd);
	serverInstance.start_server();
	/* Wait for events forever */
	while (1)
	{
		int n = epoll_wait(efd, events, MAX_EVENTS, -1);
		if (n == -1)
		{
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < n; ++i)
		{
			printf("events[%d].data.fd = %d\n", i, events[i].data.fd);
			if (events[i].data.fd == serverInstance.get_server_fd())
			{
				/* New client connection */
				serverInstance.accept_client();
				// close(events[i].data.fd);
			}
			else if (serverInstance.is_client(events[i].data.fd))
			{
				printf("received a client event\n");
				printf("events[%d].data.fd = %d\n", i, events[i].data.fd);
				serverInstance.handle_client(events[i].data.fd);
				printf("end handling client\n\n\n\n");

			}
		}
	}


	
	
	return 0;
}
