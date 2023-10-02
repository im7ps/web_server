/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:04:51 by sgerace           #+#    #+#             */
/*   Updated: 2023/10/02 16:23:17 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

int ps_create_matrix(std::ifstream& confFile)
{
    std::string line;

    while (std::getline(confFile, line))
    {
        std::cout << line << std::endl;
    }
    return 0;
}

bool ps_cfile(const char* path)
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
        std::cerr << "Errore: " << e.what() << std::endl;
    }

    if (ps_create_matrix(confFile))
        return false;

    confFile.close();
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
        if (!ps_cfile("./configuration_files/default.txt"))
            return 1;
    }

    else
    {
        if (!ps_cfile(argv[1]))
            return 1;
    }
    return 0;
}
