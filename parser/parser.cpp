/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:15:40 by sgerace           #+#    #+#             */
/*   Updated: 2023/10/13 21:05:45 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.hpp"

Required::Required() 
{
        attributes[0] = "server";
        attributes[1] = "host";
        attributes[2] = "port";
        attributes[3] = "error_page";
        attributes[4] = "max_client_body_size";
        attributes[5] = "location";
        attributes[6] = "methods";
        attributes[7] = "redirect";
        attributes[8] = "directory";
        attributes[9] = "directory_listening";
        attributes[10] = "default_file";
        attributes[11] = "execute_cgi";
        attributes[12] = "upload_directory";
}

Required::~Required()
{
	std::cout << "Destroyed Required object\n";
}

const std::string* Required::getAttributes() 
{
	return attributes;
}

int Required::findAttribute(const std::string& target) const
{
    for (int i = 0; i < 13; ++i)
	{
        if (attributes[i] == target)
		{
            return i;  // Restituisci l'indice se la stringa è stata trovata.
        }
    }
    return -1; // Se la stringa non è stata trovata, restituisci -1.
}
