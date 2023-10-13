/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_curlyb.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:31:44 by stepis            #+#    #+#             */
/*   Updated: 2023/10/13 17:00:04 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

int ps_check_curlyb(std::string line)
{
	static int	counter;
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
