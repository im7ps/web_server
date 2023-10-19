/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:04:51 by sgerace           #+#    #+#             */
/*   Updated: 2023/10/19 17:03:03 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

void argc_checker(int argc, char** argv, std::string& path);

int main (int argc, char** argv)
{
	std::string				path;
	ConfigData				configMap;

	try
	{
		argc_checker(argc, argv, path);
		ps_fill_vector(path, configMap);
		ps_check_list(configMap);
		//printConfigData(configMap);
		
		socket_handler(configMap);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what();
	}
	return 0;
}
