/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_server.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:11:29 by stepis            #+#    #+#             */
/*   Updated: 2023/10/10 19:11:55 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

void ps_check_server(std::string value)
{
	// std::cout << "|" << value << "|" << std::endl;
	if (value != "{")
		throw SyntaxError();
}
