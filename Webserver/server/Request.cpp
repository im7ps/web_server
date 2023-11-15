/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcotza <dcotza@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/11/14 23:16:46 by dcotza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/Request.hpp"
#include <algorithm>

Request::Request()
{
	this->method = "";
	this->path = "";
	this->dir_path = "";
	this->filename = "";
	this->extension = "";
	this->query = "";
	this->version = "";
	this->host = "";
	this->sport = "";
	this->iport = 0;
	this->user_agent = "";
	this->connection = "";
	this->accept = "";
	this->accept_encoding = "";
	this->accept_language = "";
	this->empty_line = false;
	this->content_type = "";
	this->content_length = "";
	this->body = "";	
}

Request::~Request()
{
	
}

void	Request::getFirstLine(const std::string& raw_str)
{
	std::string line;
    std::istringstream iss(raw_str);
    
    if (std::getline(iss, line))
    {
        std::istringstream lineStream(line);
        std::string method;
        std::string path;
        std::string version;
        
        // Estrai il metodo, il percorso e la versione dalla prima riga
        if (lineStream >> method >> path >> version)
        {
            this->method = method;
            this->version = version;

			// Ora separa il percorso dalla stringa di query
            size_t idx = path.find('?');
            if (idx != std::string::npos)
            {
                this->path = path.substr(0, idx);
                this->query = path.substr(idx + 1);
            }
            else
            {
                this->path = path;
            }
			this->dir_path = this->path.substr(0, this->path.find_last_of("/") + 1);
			this->filename = this->path.substr(this->path.find_last_of("/") + 1);
			this->extension = this->filename.substr(this->filename.find_last_of(".") + 1);
			printf("extension %s \n", this->path.c_str());
			if (this->dir_path == "/test/")
			{
				this->dir_path.erase();
				this->dir_path = "/var/www/";
			}
			std::transform(this->method.begin(), this->method.end(), this->method.begin(), ::tolower);
        }	
	}
	else
	{
		perror("No first line found in request");
	    exit(EXIT_FAILURE);
	}
}

void	Request::init_host(std::string& value)
{
	const char* cvalue;
	std::size_t idx = value.find(':');
	if (idx != std::string::npos)
	{
		this->host = value.substr(1, idx - 1);
		cvalue = value.substr(idx + 1).c_str();
		this->sport = cvalue;
		this->iport = atoi(cvalue);
		this->ihost = hostnametoip(this->host, this->iport);
	}
	else
	{
		this->host = value;
	}
}

void	Request::getHeaderValues(const std::string& raw_str)
{
	std::string line;
    std::istringstream iss(raw_str);

	std::getline(iss, line); //skipping first line
	
    while(std::getline(iss, line))
    {
		//TODO salvare il body se viene trovata una stringa vuota, il body inizierà nella riga successiva alla riga vuota
/* 		if (line.empty() || line == "\n" || line == "\r")
		{
			std::cout << "DEBUG EMPTY LINE" << std::endl;
			this->empty_line = true;
			std::getline(iss, line);
			this->body = line;
		} */
/* 		else
		{ */
			std::size_t idx = line.find(':');
			if (idx != std::string::npos)
			{
				std::string key = line.substr(0, idx);
				std::string value = line.substr(idx + 1);

				// Assegna i valori alle variabili a seconda della chiave
				if (key == "Host") {
					init_host(value);
				} else if (key == "User-Agent") {
					user_agent = value;
				} else if (key == "Connection") {
					connection = value;
				} else if (key == "Accept") {
					accept = value;
				} else if (key == "Accept-Encoding") {
					accept_encoding = value;
				} else if (key == "Accept-Language") {
					accept_language = value;
				} else if (key == "Content-Type") {
					content_type = value;
				} else if (key == "Content-Length") {
					content_length = value;
				}
			}
			else
			{			
				std::cout << "DEBUG EMPTY LINE" << std::endl;
				this->empty_line = true;
				std::getline(iss, line);
				this->body = line;
			}		
		
	}
}

Request::Request(std::string& raw_str)
{
	this->getFirstLine(raw_str);
	this->getHeaderValues(raw_str);
}
