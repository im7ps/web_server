/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_init_struct.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:21:27 by stepis            #+#    #+#             */
/*   Updated: 2023/10/19 14:54:25 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

void	ps_init_server_node(ServerNode& serverNode)
{
	serverNode.serverFieldMap.insert(std::make_pair("server", &serverNode.server_id));
	serverNode.serverFieldMap.insert(std::make_pair("server_name", &serverNode.server_name));
	serverNode.serverFieldMap.insert(std::make_pair("listen", &serverNode.listen));
	serverNode.serverFieldMap.insert(std::make_pair("error_page", &serverNode.error_page));
	serverNode.serverFieldMap.insert(std::make_pair("max_client_body_size", &serverNode.max_client_body_size));
}

void	ps_init_location_node(LocationNode& locationNode)
{
	locationNode.locationFieldMap.insert(std::make_pair("location", &locationNode.location));
	locationNode.locationFieldMap.insert(std::make_pair("root", &locationNode.root));
	locationNode.locationFieldMap.insert(std::make_pair("index", &locationNode.index));
	locationNode.locationFieldMap.insert(std::make_pair("cgi_extension", &locationNode.cgi_extension));
	locationNode.locationFieldMap.insert(std::make_pair("autoindex", &locationNode.autoindex));
	locationNode.locationFieldMap.insert(std::make_pair("methods", &locationNode.methods));
	locationNode.locationFieldMap.insert(std::make_pair("redirect", &locationNode.redirect));
	locationNode.locationFieldMap.insert(std::make_pair("directory", &locationNode.directory));
	locationNode.locationFieldMap.insert(std::make_pair("default_file", &locationNode.default_file));
	locationNode.locationFieldMap.insert(std::make_pair("execute_cgi", &locationNode.execute_cgi));
	locationNode.locationFieldMap.insert(std::make_pair("upload_directory", &locationNode.upload_directory));
	locationNode.locationFieldMap.insert(std::make_pair("directory_listening", &locationNode.directory_listening));
}