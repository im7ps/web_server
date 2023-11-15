/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcotza <dcotza@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/11/14 23:17:50 by dcotza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */


#include "../includes/ServerConfig.hpp"

void ServerConfig::populate_server_nodes(config_context *curr_context)
{
	if (curr_context->is_server && !curr_context->is_location && curr_context->tokens.size() > 0)
	{
		if (curr_context->tokens[0] == "server")
		{
			server_node server_node;
			
			init_server_node(&server_node);
			this->server_nodes.push_back(server_node);
		} else if (curr_context->tokens[0] == "host")
		{
			this->server_nodes.back().host = curr_context->tokens[1];
			this->server_nodes.back().host_digit = hostnametoip(this->server_nodes.back().host, this->server_nodes.back().port);
			this->server_nodes.back().host_digit = hostnametoip(this->server_nodes.back().host, this->server_nodes.back().port);
			std::cout << "host_digit: " << this->server_nodes.back().host_digit << std::endl;
			std::cout << "host: " << this->server_nodes.back().host << std::endl;
		}
		else if (curr_context->tokens[0] == "listen")
			this->server_nodes.back().port = atoi(curr_context->tokens[1].c_str());
		else if (curr_context->tokens[0] == "server_name")
		{
			for (size_t i = 1; i < curr_context->tokens.size(); i++)
				this->server_nodes.back().server_names.push_back(curr_context->tokens[i]);
			// this->server_nodes.back().server_name_digit = hostnametoip(this->server_nodes.back().server_name, this->server_nodes.back().port);
			for (size_t i = 1; i < curr_context->tokens.size(); i++)
				this->server_nodes.back().server_names.push_back(curr_context->tokens[i]);
			// this->server_nodes.back().server_name_digit = hostnametoip(this->server_nodes.back().server_name, this->server_nodes.back().port);
		}
		else if (curr_context->tokens[0] == "root")
			this->server_nodes.back().root = curr_context->tokens[1];
		else if (curr_context->tokens[0] == "index")
			this->server_nodes.back().index = curr_context->tokens[1];
		else if (curr_context->tokens[0] == "error_page")
		{
			error_page error_page;
			error_page.error_code = curr_context->tokens[1];
			error_page.error_page_path = curr_context->tokens[2];
			this->server_nodes.back().error_pages.push_back(error_page);
		}
		else if (curr_context->tokens[0] == "body_size")
			this->server_nodes.back().body_size = curr_context->tokens[1];
		else if (curr_context->tokens[0] == "path_cgi_bin")
			this->server_nodes.back().php_cgi_bin_path = curr_context->tokens[1];
	}
}

void ServerConfig::print_location_nodes(server_node *srv_node)
{
	for (std::list<location_node>::iterator it = srv_node->locations.begin(); it != srv_node->locations.end(); it++)
	{
		std::cout << "location_path: " << it->path << std::endl;
		for (std::list<std::string>::iterator it2 = it->methods.begin(); it2 != it->methods.end(); it2++)
			std::cout << "location_method: " << *it2 << std::endl;
		std::cout << "location_index: " << it->index << std::endl;
	}
}

void ServerConfig::populate_location_nodes(config_context *curr_context)
{
	if (curr_context->is_server && curr_context->is_location && curr_context->tokens.size() > 0)
	{
		if (curr_context->tokens[0] == "location")
		{
			location_node loc_node;
			
			init_location_node(&loc_node, curr_context->tokens[1]);
			this->server_nodes.back().locations.push_back(loc_node);
		} else if (curr_context->tokens[0] == "method")
		{
			this->server_nodes.back().locations.back().methods.clear();
			for (size_t i = 1; i < curr_context->tokens.size(); i++)
				this->server_nodes.back().locations.back().methods.push_back(std::string(curr_context->tokens[i]));
		}
		else if (curr_context->tokens[0] == "index")
			this->server_nodes.back().locations.back().index = curr_context->tokens[1];
		else if (curr_context->tokens[0] == "autoindex")
			this->server_nodes.back().locations.back().autoindex = curr_context->tokens[1] == "on" ? true : false;
		else if (curr_context->tokens[0] == "redirect")
			this->server_nodes.back().locations.back().redirect = curr_context->tokens[1];
		else if (curr_context->tokens[0] == "redirect")
			this->server_nodes.back().locations.back().redirect = curr_context->tokens[1];
	}
}


int ServerConfig::parse_config_file(char *config_file_path)
{
	std::ifstream config_file(config_file_path);
	if (!config_file.is_open())
		throw std::runtime_error("Impossibile aprire il file di configurazione");
	std::string line;

	config_context curr_context;
	init_config_context(&curr_context);
	
	while (std::getline(config_file, line))
	{
		curr_context.tokens.clear();
		for (size_t i = 0; i < line.length(); i++)
		{
			if (line[i] == '#')
				break;
			if (update_config_contex(&curr_context, line[i]))
				break;
			if (is_whitespace(line[i]))
				continue;
			std::string token;
			while (!is_whitespace(line[i]) && line[i] != '{' && line[i] && line[i] != ';')
			{
				token += std::tolower(line[i]);
				i++;
			}
			curr_context.tokens.push_back(token);
		}
		this->populate_server_nodes(&curr_context);
		this->populate_location_nodes(&curr_context);
	}
	// print_server_nodes(true);
	config_file.close();
	return (0);
}

void print_server_node(server_node *server_node)
{
	std::cout << "host: " << server_node->host << std::endl;
	std::cout << "host_digit: " << server_node->host_digit << std::endl;
	std::cout << "port: " << server_node->port << std::endl;
	// std::cout << "server_name: " << server_node->server_names << std::endl;
	std::cout << "root: " << server_node->root << std::endl;
	std::cout << "index: " << server_node->index << std::endl;
	std::cout << "body_size: " << server_node->body_size << std::endl;
	std::cout << "autoindex: " << server_node->autoindex << std::endl;
}

void ServerConfig::print_server_nodes(bool locations)
{
	std::list<server_node>::iterator it;
	std::list<error_page>::iterator it2;
	std::list<location_node>::iterator it3;
	std::list<std::string>::iterator it4;

	for (it = this->server_nodes.begin(); it != this->server_nodes.end(); it++)
	{
		print_server_node(&(*it));
		for (it2 = it->error_pages.begin(); it2 != it->error_pages.end(); it2++)
		{
			std::cout << "error_code: " << it2->error_code << std::endl;
			std::cout << "error_page_path: " << it2->error_page_path << std::endl;
		}
		if (locations)
		{
			for (it3 = it->locations.begin(); it3 != it->locations.end(); it3++)
			{
				std::cout << "location_path: " << it3->path << std::endl;
				for (it4 = it3->methods.begin(); it4 != it3->methods.end(); it4++)
					std::cout << "location_method: " << *it4 << std::endl;
				std::cout << "location_index: " << it3->index << std::endl;
			}
		}
		std::cout << std::endl;
	}
}

void validate_server_node(server_node *server_node)
{
	if (server_node->host_digit == INADDR_NONE)
		throw std::runtime_error("Syntax error in config file: invalid host");
	if (server_node->port < 0 || server_node->port > 65535)
		throw std::runtime_error("Syntax error in config file: invalid port");
	// if (server_node->server_names == "")
		// throw std::runtime_error("Syntax error in config file: invalid server_name");
	// if (server_node->server_names == "")
		// throw std::runtime_error("Syntax error in config file: invalid server_name");
	if (opendir(server_node->root.c_str()) == NULL)
		throw std::runtime_error("Syntax error in config file: invalid root");
}

void validate_location_node(location_node *location_node)
{
	if (location_node->path == "")
		throw std::runtime_error("Syntax error in config file: invalid location path");
}

//check for server with same host and port
void check_for_duplicates(std::list<server_node> server_nodes)
{
	std::list<server_node>::iterator it;
	std::list<server_node>::iterator it2;

	for (it = server_nodes.begin(); it != server_nodes.end(); it++)
	{
		for (it2 = server_nodes.begin(); it2 != server_nodes.end(); it2++)
		{
			for (std::list<location_node>::iterator it3 = it->locations.begin(); it3 != it->locations.end(); it3++)
			{
				for (std::list<location_node>::iterator it4 = it2->locations.begin(); it4 != it2->locations.end(); it4++)
				{
					if (it != it2 && it->host == it2->host && it->port == it2->port && it3->path == it4->path)
					{
						print_server_node(&(*it));
						print_server_node(&(*it2));
						throw std::runtime_error("Syntax error in config file: found 2 servers with identical name, port, ip");
					}
				}
			}
			// if (it != it2 && it->host == it2->host && it->port == it2->port && it->server_name == it2->server_name)
			// {
				// print_server_node(&(*it));
				// print_server_node(&(*it2));
				// throw std::runtime_error("Syntax error in config file: found 2 servers with identical name, port, ip");
			// }
		}
	}
			for (std::list<location_node>::iterator it3 = it->locations.begin(); it3 != it->locations.end(); it3++)
			{
				for (std::list<location_node>::iterator it4 = it2->locations.begin(); it4 != it2->locations.end(); it4++)
				{
					if (it != it2 && it->host == it2->host && it->port == it2->port && it3->path == it4->path)
					{
						print_server_node(&(*it));
						print_server_node(&(*it2));
						throw std::runtime_error("Syntax error in config file: found 2 servers with identical name, port, ip");
					}
				}
			}
			// if (it != it2 && it->host == it2->host && it->port == it2->port && it->server_name == it2->server_name)
			// {
				// print_server_node(&(*it));
				// print_server_node(&(*it2));
				// throw std::runtime_error("Syntax error in config file: found 2 servers with identical name, port, ip");
			// }
		}
	}
}

void validate_config_file(std::list<server_node> server_nodes)
{
	std::list<server_node>::iterator it;
	for (it = server_nodes.begin(); it != server_nodes.end(); it++)
	{
		validate_server_node(&(*it));
		for (std::list<location_node>::iterator it2 = it->locations.begin(); it2 != it->locations.end(); it2++)
			validate_location_node(&(*it2));
	}

}

ServerConfig::ServerConfig(char *config_file_path)
{
	try {
		parse_config_file(config_file_path);
		validate_config_file(this->server_nodes);
		check_for_duplicates(this->server_nodes);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}

ServerConfig::~ServerConfig()
{
}