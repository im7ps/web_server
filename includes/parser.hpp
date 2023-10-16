/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:30:26 by stepis            #+#    #+#             */
/*   Updated: 2023/10/16 15:44:40 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

#include "libraries.hpp"

enum RequiredParams {
    SERVER,
    HOST,
    PORT,
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

struct Location {
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
};

struct Server {
	std::string server_name;
	std::string host;
	std::string port;
	std::string error_page;
	std::string max_client_body_size;
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
	std::string host;
	std::string port;
	std::string error_page;
	std::string max_client_body_size;
	std::list<LocationNode> locationList;
    std::multimap<std::string, std::string*> serverFieldMap;
};

struct ConfigData {
	Server server;
	Location location;
	std::list<ServerNode> serverList;
};


void		ps_create_vector(const std::string path, std::list<ServerNode>& serverList, Server*& serverArray);
void		ps_check_server(std::string value);
void		ps_check_location(std::string value);
int			ps_check_curlyb(std::string line);
std::string ft_itos(int number);
void		ft_trim(std::string& str);
void		print_server_array(const Server* serverArray, size_t arraySize);
void		delete_server_array(Server* serverArray, size_t arraySize);

#endif