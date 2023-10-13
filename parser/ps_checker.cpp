/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_checker.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:12:36 by stepis            #+#    #+#             */
/*   Updated: 2023/10/13 17:20:17 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.hpp"

// viene controllato che i vari campi del cfile esistano e siano assegnati a valori accettati
int ps_check_map(std::vector<std::pair<std::string, std::string> > &configMap)
{
	Required	Required;
	int			count_elem = 0;

	for (std::vector<std::pair<std::string, std::string> >::iterator it = configMap.begin(); it != configMap.end(); ++it)
	{
		
		//std::cout << "Chiave: " << it->first << ", Valore: " << it->second << std::endl;
	}
	if (count_elem != ELEM_NUM)
		throw std::runtime_error("One or more parameters in the configuration file are missing\n");
	return 0;
}
