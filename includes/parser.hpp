/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:30:26 by stepis            #+#    #+#             */
/*   Updated: 2023/10/12 18:48:12 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

#include "libraries.hpp"

enum RequiredOptions {
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

struct Required {
    private:
        int server;
        int host;
        int port;
        int error_page;
        int max_client_body_size;
        int location;
        int methods;
        int redirect;
        int directory;
        int directory_listening;
        int default_file;
        int execute_cgi;
        int upload_directory;
    public:
        Required()
        {
            this->server = 0;
            this->host = 0;
            this->port = 0;
            this->error_page = 0;
            this->max_client_body_size = 0;
            this->location = 0;
            this->methods = 0;
            this->redirect = 0;
            this->directory = 0;
            this->default_file = 0;
            this->execute_cgi = 0;
            this->upload_directory = 0;
            this->directory_listening = 0;
        }
        ~Required()
        {
            std::cout << "Destroyed Required object\n";
        }
		void router(int token)
		{
			switch (token)
			{
				case SERVER:
					std::cout << "Opzione selezionata: SERVER" << std::endl;
					break;
				case HOST:
					std::cout << "Opzione selezionata: HOST" << std::endl;
					break;
				// Aggiungi i casi per le altre opzioni qui
				default:
					std::cout << "Opzione non riconosciuta" << std::endl;
					break;
    		}
		}
        int getServer()
        {
            return this->server;
        }
        void setServer(int num)
        {
            this->server = num;
        }
};

bool	ps_create_map(const std::string path, std::vector<std::pair<std::string, std::string> > &configMap);
void	ps_create_map2(std::ifstream& confFile, std::vector<std::pair<std::string, std::string> > &congifMap);
int		ps_check_map(std::vector<std::pair<std::string, std::string> > &configMap);
int		ps_router(std::vector<std::pair<std::string, std::string> >::iterator it, Required& Required);
void	ps_check_server(std::string value);
void	ps_check_location(std::string value);
int		ps_check_curlyb(std::string line);
void	ft_trim(std::string& str);


#endif