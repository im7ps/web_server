/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:04:51 by sgerace           #+#    #+#             */
/*   Updated: 2023/10/16 16:01:05 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

void argc_checker(int argc, char** argv, std::string& path);

void printConfigData(ConfigData& data) {
	std::list<ServerNode>::iterator currentS = data.serverList.begin();
	std::list<LocationNode>::iterator currentL;
	int i = 0;
	int j = 0;
	
	while (currentS != data.serverList.end())
	{
		++j;
		i = 0;
		std::cout << "Server" << j << ": " << currentS->server_name << std::endl;

		for (currentL = currentS->locationList.begin(); currentL != currentS->locationList.end(); ++currentL)
		{
			++i;
			std::cout << "Location " << i << ": " << currentL->location << std::endl;
		}
		++currentS;
	}
}

void	ps_init_server_node(ServerNode& serverNode)
{
	serverNode.serverFieldMap.insert(std::make_pair("server", &serverNode.server_id));
	serverNode.serverFieldMap.insert(std::make_pair("server_name", &serverNode.server_name));
	serverNode.serverFieldMap.insert(std::make_pair("host", &serverNode.host));
	serverNode.serverFieldMap.insert(std::make_pair("port", &serverNode.port));
	serverNode.serverFieldMap.insert(std::make_pair("error_page", &serverNode.error_page));
	serverNode.serverFieldMap.insert(std::make_pair("max_client_body_size", &serverNode.max_client_body_size));
}

void	ps_init_location_node(LocationNode& locationNode)
{
	locationNode.locationFieldMap.insert(std::make_pair("location", &locationNode.location));
	locationNode.locationFieldMap.insert(std::make_pair("root", &locationNode.root));
	locationNode.locationFieldMap.insert(std::make_pair("index", &locationNode.index));
	locationNode.locationFieldMap.insert(std::make_pair("cgi_extension", &locationNode.cgi_extension));
	locationNode.locationFieldMap.insert(std::make_pair("autoindex", &locationNode.autoindex));
	locationNode.locationFieldMap.insert(std::make_pair("methods", &locationNode.methods));
	locationNode.locationFieldMap.insert(std::make_pair("redirect", &locationNode.redirect));
	locationNode.locationFieldMap.insert(std::make_pair("directory", &locationNode.directory));
	locationNode.locationFieldMap.insert(std::make_pair("default_file", &locationNode.default_file));
	locationNode.locationFieldMap.insert(std::make_pair("execute_cgi", &locationNode.execute_cgi));
	locationNode.locationFieldMap.insert(std::make_pair("upload_directory", &locationNode.upload_directory));
	locationNode.locationFieldMap.insert(std::make_pair("directory_listening", &locationNode.directory_listening));
}

void	ps_fill_vector(const std::string path, ConfigData& data)
{
	int			counter = 0;
	std::string	key;
	std::string	value;
    std::string line;
	std::list<ServerNode>::iterator currentServer;

	std::ifstream configFile(path.c_str());
    if (!configFile) {
        std::cerr << "Impossibile aprire il file di configurazione: " << std::endl;
        return;
    }

    while (std::getline(configFile, line))
	{
		ft_trim(line);
		ps_check_curlyb(line);
		std::istringstream iss(line);
		if (std::getline(iss, key, ' ') && std::getline(iss, value, '\n'))
		{
			//std::cout << "key: " << key << "| " << std::endl;
			//std::cout << "value: " << value << "| " << std::endl;
			if (key == "server" && key != "server_name") {
				data.serverList.push_back(ServerNode());
				ps_init_server_node(data.serverList.back());
				currentServer = --data.serverList.end();
			}

			if (key == "location" && currentServer != data.serverList.end()) {
				currentServer->locationList.push_back(LocationNode());
				ps_init_location_node(currentServer->locationList.back());
			}

			if (!data.serverList.empty() && currentServer != data.serverList.end()) {
				for (std::multimap<std::string, std::string*>::iterator it = currentServer->serverFieldMap.find(key); it != currentServer->serverFieldMap.end() && it->first == key; ++it) {
					*(it->second) = value;
					//std::cout << it->first << ": " << *(it->second) << "|" << std::endl;
				}
			}

			if (!data.serverList.empty() && !currentServer->locationList.empty()) {
				for (std::multimap<std::string, std::string*>::iterator it = currentServer->locationList.back().locationFieldMap.find(key); it != currentServer->locationList.back().locationFieldMap.end() && it->first == key; ++it) {
					*(it->second) = value;
					//std::cout << it->first << ": " << *(it->second) << "|" << std::endl;
				}
			}
		}
    }
	counter = ps_check_curlyb("");
	if (counter != 0)
		throw SyntaxError();
	//std::cout << "Lunghezza lista server: " << data.serverList.size() << std::endl;
    configFile.close();
}

int main (int argc, char** argv)
{
	std::string				path;
	ConfigData				configMap;

	try
	{
		argc_checker(argc, argv, path);
		ps_fill_vector(path, configMap);
		//printConfigData(configMap);
		//ps_check_map(configMap);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what();
	}
	return 0;
}

//print_server_array(serverArray, serverList.size());