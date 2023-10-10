/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_location.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:11:10 by stepis            #+#    #+#             */
/*   Updated: 2023/10/10 19:11:45 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

void ps_check_location(std::string value)
{
	int counter = 0;
	
	for (int i = 0; i < value.length(); ++i) {
		if (value[i] == '{') {
			counter++;
		}
	}

	if ((value.find('{') != value.length() - 1) || counter != 1)
	{
		std::cout << counter << ": counter\n";
		std::cout << value << ": STRING\n";
		std::cout << value[value.length() - 1] << ": INDEX\n";
		throw SyntaxError();
	}
}
