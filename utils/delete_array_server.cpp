/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_array_server.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:42:08 by stepis            #+#    #+#             */
/*   Updated: 2023/10/14 20:43:14 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

void	delete_server_array(Server* serverArray, size_t arraySize)
{
	std::cout << arraySize << std::endl;

	for (size_t i = 0; i < arraySize; ++i) {
		delete[] serverArray[i].locations;
	}
	delete[] serverArray;
}
