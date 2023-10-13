/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_curlyb.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:31:44 by stepis            #+#    #+#             */
/*   Updated: 2023/10/13 16:44:44 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

int ps_check_curlyb(std::string line)
{
	static int counter;


	if (!line.empty())
	{
		if (line.find('{') != line.length() - 1)
		{
			counter++;
		}
		else if (line[0] == '}') //se e l unico carattere presente
		{
			//std::cout << line << "asd" << std::endl;
			counter--;
		}
	}
	return counter;
}
