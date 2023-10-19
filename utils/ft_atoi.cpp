/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:34:21 by stepis            #+#    #+#             */
/*   Updated: 2023/10/19 14:54:54 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

bool isNumeric(const std::string& str)
{
    for (size_t i = 0; i < str.length(); ++i) {
        if (!std::isdigit(str[i]) && str[i] != '\0') {
            return false;
        }
    }
    return true;
}

int	ft_atoi(const std::string& str)
{
	int	result;

	if (!isNumeric(str))
		throw std::runtime_error("Listen value is not numeric\n");
	std::stringstream ss(str);
	ss >> result;
	return result;
}
