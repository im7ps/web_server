/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:08:14 by stepis            #+#    #+#             */
/*   Updated: 2023/10/10 19:08:31 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

void argc_checker(int argc, char** argv, std::string& path)
{
	if (argc > 2)
	{
		throw std::runtime_error("USAGE: ./webserver [CONFIGURATION_FILE]\n");
	}
	if (argc == 1)
	{
		path = "./configuration_files/default.txt";
	}
	else
	{
		path = argv[1];
	}
}
