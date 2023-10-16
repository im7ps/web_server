/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_fill_vector.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:21:44 by stepis            #+#    #+#             */
/*   Updated: 2023/10/16 23:02:30 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

void	ps_fill_vector(const std::string path, ConfigData& data)
{
	int								counter = 0;
	std::string						key;
	std::string						value;
    std::string						line;
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
					*(it->second) = ft_trim(value);
					//std::cout << it->first << ": " << *(it->second) << "|" << std::endl;
				}
			}

			if (!data.serverList.empty() && !currentServer->locationList.empty()) {
				for (std::multimap<std::string, std::string*>::iterator it = currentServer->locationList.back().locationFieldMap.find(key); it != currentServer->locationList.back().locationFieldMap.end() && it->first == key; ++it) {
					*(it->second) = ft_trim(value);
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