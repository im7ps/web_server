/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:04:51 by sgerace           #+#    #+#             */
/*   Updated: 2023/10/14 20:43:14 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

void argc_checker(int argc, char** argv, std::string& path);

int main (int argc, char** argv)
{
	std::list<ServerNode>	serverList;
	std::string				path;
	Server*					serverArray;

	try
	{
		argc_checker(argc, argv, path);
		ps_create_vector(path, serverList, serverArray);
		//ps_fill_vector(path, serverArray);
		//ps_check_map(configMap);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what();
	}

	delete_server_array(serverArray, serverList.size());
	return 0;
}
