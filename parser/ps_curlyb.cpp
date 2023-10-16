/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_curlyb.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:31:44 by stepis            #+#    #+#             */
/*   Updated: 2023/10/16 16:00:12 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

int ps_check_curlyb(std::string line)
{
	static int	counter = 0;
	int			index;

	if (!line.empty())
	{
		index = line.find('{');
		if (index != std::string::npos)
		{
			if (index == line.length() - 1)
			{
				counter++;
			}
			else
			{
				throw SyntaxError();
			}
		}
		else if (line[0] == '}') //se e l unico carattere presente nella riga
		{
			counter--;
		}
	}
	return counter;
}
