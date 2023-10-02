/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:04:51 by sgerace           #+#    #+#             */
/*   Updated: 2023/10/02 16:59:09 by sgerace          ###   ########.fr       */
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

int ps_create_list_2(std::ifstream& confFile)
{
    std::string line;
    std::vector<std::pair<std::string, std::string> > elements;

    while (std::getline(confFile, line))
    {
        ft_trim(line);        

        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::cout << line << std::endl;

        std::cout << "---------------" << std::endl;

        size_t pos = line.find(' ');
        if (pos != std::string::npos) 
        {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            elements.push_back(std::make_pair(key, value));
        }
    }

    for (std::vector<std::pair<std::string, std::string> >::iterator it = elements.begin(); it != elements.end(); ++it) 
    {
        std::cout << "Chiave: " << it->first << ", Valore: " << it->second << std::endl;
    }


    return 0;
}

bool ps_create_list(const char* path)
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

    if (ps_create_list_2(confFile))
        return false;

    confFile.close();

    //dovrá ritornare la lista
    return true;
}

int main (int argc, char** argv)
{
    if (argc > 2)
    {
        std::cout << "USAGE: ./webserver [CONFIGURATION_FILE].\n";
        return 1;
    }

    if (argc == 1)
    {
        if (!ps_create_list("./configuration_files/default.txt"))
            return 1;
    }

    else
    {
        if (!ps_create_list(argv[1]))
            return 1;
    }
    return 0;
}
