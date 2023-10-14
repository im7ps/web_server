/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:30:26 by stepis            #+#    #+#             */
/*   Updated: 2023/10/14 19:29:59 by stepis           ###   ########.fr       */
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

#define PARAM_NUM 13

class Required {
    private:
		std::string attributes[13];
    public:
        Required();
        ~Required();
		const std::string* getAttributes();
		int findAttribute(const std::string& target) const;
};

typedef struct s_global {
	const std::string host;
	const std::string port;
	const std::string error_page;
	const std::string max_client_body_size;
	const std::string directory_listening;
}	t_global;

struct Location {
	int			indice;
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
	int			indice;
	int			location_num;
	std::string server_name;
	std::string host;
	std::string port;
	std::string error_page;
	std::string max_client_body_size;
	Location* locations;
};

struct ServerNode {
    int location_count;
};

void	ps_create_vector(const std::string path, std::list<ServerNode>& serverList);
int			ps_check_map(std::vector<std::pair<std::string, std::string> >& configMap);
int			ps_router(std::vector<std::pair<std::string, std::string> >::iterator it, Required& Required);
void		ps_check_server(std::string value);
void		ps_check_location(std::string value);
int			ps_check_curlyb(std::string line);
std::string ft_itos(int number);
void		ft_trim(std::string& str);


#endif