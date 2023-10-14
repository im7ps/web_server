/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_map.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:13:29 by stepis            #+#    #+#             */
/*   Updated: 2023/10/14 19:38:31 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

void	ps_count_elem(std::ifstream& confFile, std::list<ServerNode>& serverList)
{
	std::string line;

    while (std::getline(confFile, line))
	{
        size_t foundServer = line.find("server ");
        size_t foundLocation = line.find("location ");

        if (foundServer != std::string::npos) {
            // trovata la stringa "server", crea un nuovo nodo nella lista
            serverList.push_back(ServerNode());
        }

        // incrementa il conteggio di "location" per l'ultimo nodo "server" nella lista
        if (!serverList.empty() && foundLocation != std::string::npos)
		{
            serverList.back().location_count++;
        }
    }
}

void	ps_init_server(Server* serverArray, std::list<ServerNode>& serverList)
{
	int i = -1;

	for (std::list<ServerNode>::iterator it = serverList.begin(); it != serverList.end(); ++it)
	{
		++i;
		serverArray[i].indice = i + 1;
		serverArray[i].location_num = it->location_count;
		serverArray[i].server_name = "";
		serverArray[i].host = "";
		serverArray[i].port = "";
		serverArray[i].error_page = "";
		serverArray[i].max_client_body_size = "";
		serverArray[i].locations = new Location[it->location_count];
		 if (!serverArray[i].locations)
			throw std::runtime_error("Memoria insufficiente\n");
	}
}

void	ps_init_locations(Server* serverArray, std::list<ServerNode>& serverList)
{
	int	j;
	int	i = -1;

	for (std::list<ServerNode>::iterator it = serverList.begin(); it != serverList.end(); ++it)
	{
		++i;
		j = -1;
		while (j < it->location_count - 1)
		{
			++j;
			serverArray[i].locations[j].indice = j + 1;
			serverArray[i].locations[j].location = "";
			serverArray[i].locations[j].root = "";
			serverArray[i].locations[j].index = "";
			serverArray[i].locations[j].cgi_extension = "";
			serverArray[i].locations[j].autoindex = "";
			serverArray[i].locations[j].methods = "";
			serverArray[i].locations[j].redirect = "";
			serverArray[i].locations[j].directory = "";
			serverArray[i].locations[j].default_file = "";
			serverArray[i].locations[j].execute_cgi = "";
			serverArray[i].locations[j].upload_directory = "";
			serverArray[i].locations[j].directory_listening = "";
		}
	}	
}


void	ps_init_vector(Server* serverArray, std::list<ServerNode>& serverList)
{
	ps_init_server(serverArray, serverList);
	ps_init_locations(serverArray, serverList);
}

void printServerArray(const Server* serverArray, size_t arraySize) {
    for (size_t i = 0; i < arraySize; ++i) {
        std::cout << "Server: " << serverArray[i].indice << std::endl;

        // Stampa le informazioni delle Location all'interno di ciascun Server
        for (int j = 0; j < serverArray[i].location_num; ++j) {
            std::cout << "Location: " << serverArray[i].locations[j].indice << std::endl; 
        }
    }
}

// se si riesce si apre il file, si manda in pasto alla funzione vector2 e poi si chiude il file
void	ps_create_vector(const std::string path, std::list<ServerNode>& serverList)
{
	Server serverArray;

	std::ifstream confFile(path.c_str());
	try
	{
		if (!confFile.is_open())
		{
			throw std::runtime_error("Impossibile aprire il file\n");
		}

		// legge il file riga per riga, conta il numero di volte che è presente la stringa server e il numero di volte che è presente la stringa location all interno di ogni server
		ps_count_elem(confFile, serverList);
	
        // Alloca dinamicamente l'array di Server
        size_t arraySize = serverList.size();
        Server* serverArray = new Server[arraySize];



		
		if (!serverArray)
		{
			throw std::runtime_error("Memoria insufficiente\n");
		}
        // Invia l'array allocato dinamicamente a ps_fill_vector
        ps_init_vector(serverArray, serverList);

		printServerArray(serverArray, arraySize);


		confFile.close();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what();
	}
}
