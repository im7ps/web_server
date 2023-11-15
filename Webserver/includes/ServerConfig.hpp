/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:16:05 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/12 11:28:25 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CONFIG_HPP
# define SERVER_CONFIG_HPP

# include <fstream>
# include <string>
# include <iostream>
# include <list>
# include <map>
# include <vector>
# include "../includes/utils.hpp"
# include "../includes/parser_utils.hpp"
# include <stdlib.h>
# include <dirent.h>


class ServerConfig
{
private:
	/* data */
	void populate_server_nodes(config_context *curr_context);
	void populate_location_nodes(config_context *curr_context);
	int	 parse_config_file(char *config_file_path);
public:
	std::list<server_node> server_nodes;

	ServerConfig(char *config_file_path);
	~ServerConfig();

	void print_server_nodes(bool locations);
	void print_location_nodes(server_node *srv_node);
};

#endif
