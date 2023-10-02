#ifndef PARSER_HPP
# define PARSER_HPP

# include <fstream>
# include <iostream>

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


bool ps_cfile(const char* path);

#endif