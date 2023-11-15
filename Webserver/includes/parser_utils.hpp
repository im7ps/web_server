/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcotza <dcotza@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:58:36 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/14 22:11:16 by dcotza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_HPP
# define PARSER_UTILS_HPP
# include <vector>

typedef struct error_page {
	std::string error_code;
	std::string error_page_path;
} error_page;

typedef struct location_node {
	std::list<std::string> methods;
	std::string path;
	std::string index;
	std::string redirect;
	bool		autoindex;
} location_node;

typedef struct server_node {
	std::string host;
	uint32_t 	host_digit;
	int port;
	std::list<std::string> server_names;
	std::string	server_name_digit;
	std::string root;
	std::string index;
	std::list<error_page> error_pages;
	std::list<location_node> locations;
	std::string body_size;
	std::string php_cgi_bin_path;
	bool autoindex;
} server_node;

typedef struct config_context {
	bool is_server;
	bool is_location;
	std::vector<std::string> tokens;
} config_context;


void		init_config_context(config_context *context);
void		init_server_node(server_node *server_node);
void		init_location_node(location_node *location_node, std::string path);
int			update_config_contex(config_context *curr_context, char chr);




# endif