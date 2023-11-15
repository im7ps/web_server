/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcotza <dcotza@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:57:22 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/14 23:07:52 by dcotza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ServerConfig.hpp"

void init_config_context(config_context *context)
{
	context->is_server = false;
	context->is_location = false;
	context->tokens.clear();
}

void init_server_node(server_node *server_node)
{
	server_node->host = "";
	server_node->port = 0;
	server_node->server_names.clear();
	server_node->root = "";
	server_node->index = "";
	server_node->error_pages.clear();
	server_node->locations.clear();
	server_node->body_size = "1000000";
	server_node->php_cgi_bin_path = "";
	server_node->autoindex = false;
}

void init_location_node(location_node *location_node, std::string path)
{
	if (path == "")
		throw std::runtime_error("Syntax error in config file: location block without path");
	location_node->methods.push_back("get");
	location_node->path = path;
	location_node->index = "";
	location_node->autoindex = false;
	location_node->redirect = "";
}

int	update_config_contex(config_context *curr_context, char chr)
{
	if (chr == '{') {
		if (curr_context->tokens[0] == "server")
		{
			if (curr_context->is_server)
				throw std::runtime_error("Syntax error in config file: server block inside another server block");
			curr_context->is_server = true;
		}
		else if (curr_context->tokens[0] == "location")
		{
			if (curr_context->is_location)
				throw std::runtime_error("Syntax error in config file: location block inside another location block");
			curr_context->is_location = true;
		}
		else if (curr_context->tokens[0] != "server" && curr_context->tokens[0] != "location")
			throw std::runtime_error("Syntax error in config file: unknown block");
	} else if (chr == '}') {
		if (curr_context->is_server && !curr_context->is_location)
			curr_context->is_server = false;
		else if (curr_context->is_location)
			curr_context->is_location = false;
		else
			throw std::runtime_error("Syntax error in config file: closing block without opening block");
	} else 
		return 0;
	return 1;
}
