/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_data.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:22:19 by stepis            #+#    #+#             */
/*   Updated: 2023/10/16 22:42:10 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

void printConfigData(ConfigData& data)
{
	std::list<ServerNode>::iterator currentS = data.serverList.begin();
	std::list<LocationNode>::iterator currentL;
	int i = 0;
	int j = 0;
	
	while (currentS != data.serverList.end())
	{
		++j;
		i = 0;
		std::cout << "Server" << j << ": " << currentS->port << std::endl;

		for (currentL = currentS->locationList.begin(); currentL != currentS->locationList.end(); ++currentL)
		{
			++i;
			std::cout << "Location " << i << ": " << currentL->location << std::endl;
		}
		++currentS;
	}
}