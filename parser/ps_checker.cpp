/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_checker.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:12:36 by stepis            #+#    #+#             */
/*   Updated: 2023/10/10 20:13:44 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

// viene controllato che i vari campi del cfile esistano e siano assegnati a valori accettati
int ps_check_map(std::map<std::string, std::string>& configMap)
{
	RequiredItems requiredItems;

	for (std::map<std::string, std::string>::iterator it = configMap.begin(); it != configMap.end(); ++it) 
	{
		std::cout << "Chiave: " << it->first << ", Valore: " << it->second << std::endl;
	}

	return 0;
}
