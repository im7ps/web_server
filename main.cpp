/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:04:51 by sgerace           #+#    #+#             */
/*   Updated: 2023/10/02 17:17:30 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

void ft_trim(std::string& str)
{
    std::string::size_type pos = str.find_last_not_of(" \t");
    if (pos != std::string::npos)
    {
        str.erase(pos + 1);
        
        pos = str.find_first_not_of(" \t");
        if (pos != std::string::npos)
        {
            str.erase(0, pos);
        }
    }
    else
    {
        str.erase(str.begin(), str.end());
    }
}

void ps_create_map_vector2(std::ifstream& confFile, std::vector<std::pair<std::string, std::string> > &vector)
{
    std::string line;

    while (std::getline(confFile, line))
    {
        ft_trim(line);        

        if (line.empty() || line[0] == '#') {
            continue;
        }

        size_t pos = line.find(' ');
        if (pos != std::string::npos) 
        {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            vector.push_back(std::make_pair(key, value));
        }
    }
    return ;
}

bool ps_create_map_vector(const char* path, std::vector<std::pair<std::string, std::string> > &vector)
{
    std::ifstream confFile(path);

    try
    {
        if (!confFile.is_open())
        {
            throw std::runtime_error("Impossibile aprire il file\n");
        }
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Errore: " << e.what();
    }

    ps_create_map_vector2(confFile, vector);
    if (vector.empty())
    {
        std::cout << "File vuoto!\n";
    }

    confFile.close();
    return true;
}

int main (int argc, char** argv)
{
    std::vector<std::pair<std::string, std::string> > vector;
    if (argc > 2)
    {
        std::cout << "USAGE: ./webserver [CONFIGURATION_FILE].\n";
        return 1;
    }

    if (argc == 1)
    {
        if (!ps_create_map_vector("./configuration_files/default.txt", vector))
            return 1;
    }

    else
    {
        if (!ps_create_map_vector(argv[1], vector))
            return 1;
    }

    for (std::vector<std::pair<std::string, std::string> >::iterator it = vector.begin(); it != vector.end(); ++it)
    {
        std::cout << "Chiave: " << it->first << ", Valore: " << it->second << std::endl;
    }
    return 0;
}
