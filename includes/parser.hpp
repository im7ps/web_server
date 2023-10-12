/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:30:26 by stepis            #+#    #+#             */
/*   Updated: 2023/10/12 17:24:32 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

#include "libraries.hpp"

# define SERVER 1
# define HOST 2
# define PORT 3
# define SERVER_NAME 4
# define ERROR_PAGE 5
# define MAX_CLIENT_BODY_SIZE 6
# define LOCATION 7
# define METHODS 8
# define REDIRECT 9
# define DIRECTORY 10
# define DEFAULT_FILE 11
# define EXECUTE_CGI 12
# define UPLOAD_DIRECTORY 13
# define DIRECTORY_LISTENING 14

struct RequiredItems {
    private:
        int server;
        int host;
        int port;
        int server_name;
        int error_page;
        int max_client_body_size;
        int location;
        int methods;
        int redirect;
        int directory;
        int default_file;
        int execute_cgi;
        int upload_directory;
        int directory_listening;
    public:
        RequiredItems()
        {
            this->server = 0;
            this->host = 0;
            this->port = 0;
            this->server_name = 0;
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
        ~RequiredItems()
        {
            std::cout << "Destroyed RequiredItems object\n";
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
void	ps_check_server(std::string value);
void	ps_check_location(std::string value);
int		ps_check_curlyb(std::string line);
void	ft_trim(std::string& str);


#endif