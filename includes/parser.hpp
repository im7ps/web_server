/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:30:26 by stepis            #+#    #+#             */
/*   Updated: 2023/10/19 16:45:07 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

#include "libraries.hpp"

#define MAX_EVENTS 10

enum RequiredParams {
    SERVER,
    HOST,
    LISTEN,
    ERROR_PAGE,
    MAX_CLIENT_BODY_SIZE,
    LOCATION,
    METHODS,
    REDIRECT,
    DIRECTORY,
    DEFAULT_FILE,
    EXECUTE_CGI,
    UPLOAD_DIRECTORY,
    DIRECTORY_LISTENING
};

struct LocationNode {
	std::string location;
	std::string root;
	std::string index;
	std::string cgi_extension;
	std::string autoindex;
	std::string methods;
	std::string redirect;
	std::string directory;
	std::string default_file;
	std::string execute_cgi;
	std::string upload_directory;
	std::string directory_listening;
    std::multimap<std::string, std::string*> locationFieldMap;
};

struct ServerNode {
	std::string	server_id;
	std::string server_name;
	std::string listen;
	std::string error_page;
	std::string max_client_body_size;
	std::list<LocationNode> locationList;
    std::multimap<std::string, std::string*> serverFieldMap;
};

struct ConfigData {
	//da aggiungere i parametri globali
	std::list<ServerNode> serverList;
};

int			ps_check_curlyb(std::string line);
void		ps_fill_vector(const std::string path, ConfigData& data);
void		ps_init_server_node(ServerNode& serverNode);
void		ps_init_location_node(LocationNode& locationNode);
void		ps_check_list(ConfigData& data);
std::string ft_itos(int number);
int			ft_atoi(const std::string& str);
std::string	ft_trim(std::string& str);
void		printConfigData(ConfigData& data);

void	socket_handler(ConfigData& configMap);

#endif