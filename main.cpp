/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:04:51 by sgerace           #+#    #+#             */
/*   Updated: 2023/10/03 18:17:25 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include "exceptions.hpp"

// vengono cancellati gli spazi alla fine della stringa, poi all inizio e infine vengono cancellate le linee vuote
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

int ps_check_curlyb(std::string line)
{
    static int counter;

    if (!line.empty())
    {
        if (!line.find('{'))
        {
            std::cout << line << std::endl;
            counter++;
        }
        else if (line[0] == '}')
        {
            std::cout << line << "asd" << std::endl;
            counter--;
        }
    }
    return counter;
}

// vengono controllate le parentesi graffe, viene pulita la linea che si legge ad ogni ciclo, linee vuote e commenti vengono saltati, si crea il vettore con i campi key-value
void ps_create_vector2(std::ifstream& confFile, std::vector<std::pair<std::string, std::string> > &vector)
{
    std::string   line;
    int           counter;

    while (std::getline(confFile, line))
    {
        ft_trim(line);
        ps_check_curlyb(line);

        if (line.empty() || line[0] == '#') 
        {
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
    counter = ps_check_curlyb("");
    std::cout << counter << std::endl;
    if (counter != 0)
        throw SyntaxError();
    return ;
}

// se si riesce si apre il file, si manda in pasto alla funzione vector2 e poi si chiude il file
bool ps_create_vector(const std::string path, std::vector<std::pair<std::string, std::string> >& vector)
{
    std::ifstream confFile(path.c_str());
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
        return false;
    }
    try
    {
        ps_create_vector2(confFile, vector);
    }
    catch (const SyntaxError& e)
    {
        std::cerr << e.what();
        return false;
    }
    if (vector.empty())
    {
        std::cout << "Configuration file non formattato correttamente\n";
    }
    confFile.close();
    return true;
}

void ps_check_server(std::string value)
{
    // std::cout << "|" << value << "|" << std::endl;
    if (value != "{")
        throw SyntaxError();
}

// indirizzamento all elemento da controllare
void ps_router(std::vector<std::pair<std::string, std::string> >::iterator it, RequiredItems& requiredItems)
{

    if (it->first == "server")
    {
        try
        {
            ps_check_server(it->second);
            requiredItems.setServer(1);
        }
        catch(const SyntaxError& e)
        {
            std::cerr << e.what();
        }
    }
    // else if (it->first == "host")
    // {
    //     std::cout << "C'é un host qui!\n";
    // }
    // else if (it->first == "port")
    // {
    //     std::cout << "C'é un port qui!\n";
    // }
    // else if (it->first == "server_name")
    // {
    //     std::cout << "C'é un server_name qui!\n";
    // }
    // else if (it->first == "error_page")
    // {
    //     std::cout << "C'é un error_page qui!\n";
    // }
    // else if (it->first == "max_client_body_size")
    // {
    //     std::cout << "C'é un max_client_body_size qui!\n";
    // }
    // else if (it->first == "location")
    // {
    //     std::cout << "C'é un location qui!\n";
    // }
    // else if (it->first == "methods")
    // {
    //     std::cout << "C'é un methods qui!\n";
    // }
    // else if (it->first == "redirect")
    // {
    //     std::cout << "C'é un redirect qui!\n";
    // }
    // else if (it->first == "directory")
    // {
    //     std::cout << "C'é un directory qui!\n";
    // }
    // else if (it->first == "default_file")
    // {
    //     std::cout << "C'é un default_file qui!\n";
    // }
    // else if (it->first == "execute_cgi")
    // {
    //     std::cout << "C'é un execute_cgi qui!\n";
    // }
    // else if (it->first == "upload_directory")
    // {
    //     std::cout << "Uploading directory yikes\n";
    // }
    // else if (it->first == "directory_listening")
    // {
    //     std::cout << "C'é un directory_listening qui!\n";
    // }
}

// viene controllato che i vari campi del cfile esistano e siano assegnati a valori accettati
int ps_check_vector(std::vector<std::pair<std::string, std::string> >& vector)
{
    RequiredItems requiredItems;

    for (std::vector<std::pair<std::string, std::string> >::iterator it = vector.begin(); it != vector.end(); ++it)
    {
        ps_router(it, requiredItems);
        std::cout << "Chiave: " << it->first << ", Valore: " << it->second << std::endl;
    }
    
    return 0;
}

int main (int argc, char** argv)
{
    std::vector<std::pair<std::string, std::string> > vector;
    std::string path;

    if (argc > 2)
    {
        std::cout << "USAGE: ./webserver [CONFIGURATION_FILE]\n";
        return 1;
    }
    if (argc == 1)
    {
        path = "./configuration_files/default.txt";
    }
    else
    {
        path = argv[1];
    }

    if (!ps_create_vector(path, vector))
        return 1;
    if (ps_check_vector(vector))
        return 1;
    return 0;
}
