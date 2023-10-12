/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_checker.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:12:36 by stepis            #+#    #+#             */
/*   Updated: 2023/10/12 17:25:23 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

// viene controllato che i vari campi del cfile esistano e siano assegnati a valori accettati
int ps_check_map(std::vector<std::pair<std::string, std::string> > &configMap)
{
	RequiredItems requiredItems;

	for (std::vector<std::pair<std::string, std::string> >::iterator it = configMap.begin(); it != configMap.end(); ++it)
	{
		//if (ps_router(it, requiredItems))
		//	return 1;
		std::cout << "Chiave: " << it->first << ", Valore: " << it->second << std::endl;
	}
	
	return 0;
}
