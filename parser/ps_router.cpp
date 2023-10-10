/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_router.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:11:32 by stepis            #+#    #+#             */
/*   Updated: 2023/10/10 19:12:16 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

// indirizzamento all elemento da controllare (da sostituire gli if con uno switchcase)
int ps_router(std::vector<std::pair<std::string, std::string> >::iterator it, RequiredItems& requiredItems)
{

	if (it->first == "server")
	{
		try
		{
			ps_check_server(it->second);
			requiredItems.setServer(1);
			//da aggiungere setServerID per riconoscere a quale server facciamo riferimento, piu avanti verra creato un vettore di mappe server e l ID del server sara l indice
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
	else if (it->first == "location")
	{
		//std::cout << "C'é un location qui!\n";
		try
		{
			ps_check_location(it->second);
			//requiredItems.setServer(1);
		}
		catch(const SyntaxError& e)
		{
			std::cout << "LOCATION\n";
			std::cerr << e.what();
			return 1;
		}
	}
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
	return 0;
}
