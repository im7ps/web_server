/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:04:51 by sgerace           #+#    #+#             */
/*   Updated: 2023/10/12 17:21:16 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

void argc_checker(int argc, char** argv, std::string& path);

int main (int argc, char** argv)
{
	//std::map<std::string, std::string> configMap;
	std::vector<std::pair<std::string, std::string> > configMap;
	std::string path;

	try
	{
		argc_checker(argc, argv, path);
		ps_create_map(path, configMap);
		ps_check_map(configMap);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what();
	}

	return 0;
}
