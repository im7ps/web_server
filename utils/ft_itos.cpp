/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itos.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:46:50 by stepis            #+#    #+#             */
/*   Updated: 2023/10/13 22:48:50 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

// Funzione per convertire un intero in una stringa
std::string ft_itos(int number)
{
    std::ostringstream ss;
    ss << number;
    return ss.str();
}