/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_map.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:13:29 by stepis            #+#    #+#             */
/*   Updated: 2023/10/13 16:52:01 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

// vengono controllate le parentesi graffe, viene pulita la linea che si legge ad ogni ciclo, linee vuote e commenti vengono saltati, si crea il vettore con i campi key-value
void ps_create_map2(std::ifstream& confFile, std::vector<std::pair<std::string, std::string> > &vector)
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
bool ps_create_map(const std::string path, std::vector<std::pair<std::string, std::string> >& configMap)
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
		return true;
	}

	try
	{
		ps_create_map2(confFile, configMap);
	}
	catch (const SyntaxError& e)
	{
		std::cerr << e.what();
		return true;
	}

	if (configMap.empty())
	{
		std::cout << "Configuration file non formattato correttamente\n";
	}
	confFile.close();
	return false;
}
