/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_checker.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:12:36 by stepis            #+#    #+#             */
/*   Updated: 2023/10/14 15:02:27 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.hpp"

void	ps_analyze_host(const std::string& line)
{
	std::cout << line << std::endl;
}

void	ps_analyze_server(std::string& line)
{
	static int server_id;

	ft_trim(line);
	if (line != "{")
	{
		throw SyntaxError();
	}
	server_id++;
	line = ft_itos(server_id);
}

int	ps_analyze_token(int index, std::string& line)
{
	try
	{
		switch (index)
		{
		case SERVER:
			ps_analyze_server(line);
			break;
		case HOST:
			ps_analyze_host(line);
			break;
		case PORT:
			//std::cout << "Port case\n";
			break;
		case ERROR_PAGE:
			//std::cout << "Error page case\n";
			break;
		case MAX_CLIENT_BODY_SIZE:
			//std::cout << "Port case\n";
			break;
		case LOCATION:
			//std::cout << "Port case\n";
			break;
		case METHODS:
			//std::cout << "Port case\n";
			break;
		case REDIRECT:
			//std::cout << "Port case\n";
			break;
		case DIRECTORY:
			//std::cout << "Port case\n";
			break;
		case DEFAULT_FILE:
			//std::cout << "Port case\n";
			break;
		case EXECUTE_CGI:
			//std::cout << "Port case\n";
			break;
		case UPLOAD_DIRECTORY:
			//std::cout << "Port case\n";
			break;
		case DIRECTORY_LISTENING:
			//std::cout << "Port case\n";
			break;
		default:
			throw std::runtime_error("One or more parameters in the configuration file are missing\n");
			break;
		}
	}
	catch (const SyntaxError& e)
	{
		return 1;
	}
	return 0;
}

// viene controllato che i vari campi del cfile esistano e siano assegnati a valori accettati
int ps_check_map(std::vector<std::pair<std::string, std::string> > &configMap)
{
	Required	required;
	int			count_elem = 0;
	int			switch_index = 0;
	
 	for (std::vector<std::pair<std::string, std::string> >::iterator it = configMap.begin(); it != configMap.end(); ++it)
	{
		switch_index = required.findAttribute(it->first);
		if (switch_index != -1)
		{
			if (ps_analyze_token(switch_index, it->second))
				throw SyntaxError();
		}
		//std::cout << "Chiave: " << it->first << ", Valore: " << it->second << std::endl;
	}
	if (count_elem != PARAM_NUM)
		throw std::runtime_error("One or more parameters in the configuration file are missing\n");
	return 0;
}
