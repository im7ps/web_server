/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array_server.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:12:32 by stepis            #+#    #+#             */
/*   Updated: 2023/10/14 20:43:03 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

void print_server_array(const Server* serverArray, size_t arraySize)
{
    for (size_t i = 0; i < arraySize; ++i)
	{
        std::cout << "Server: " << serverArray[i].indice << std::endl;

        for (int j = 0; j < serverArray[i].location_num; ++j)
		{
            std::cout << "Location: " << serverArray[i].locations[j].indice << std::endl; 
        }
    }
}
