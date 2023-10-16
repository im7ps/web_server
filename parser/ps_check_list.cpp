/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_check_list.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:31:18 by stepis            #+#    #+#             */
/*   Updated: 2023/10/16 23:03:55 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libraries.hpp"

static void	ps_check_server(std::string& value)
{
	static int index = 0;
	if (value.empty())
		throw std::runtime_error("Server value is not valid\n");
	value = ft_itos(++index);
}

static void ps_check_server_port(std::string& value)
{
	int	listen = 0;

	if (value.empty() || value == ";" || value.length() > 6)
		throw std::runtime_error("Port value is not valid\n");

	listen = ft_atoi(value);
	if (listen < 0 || listen > 65535)
		throw std::runtime_error("Port value is too big or too small\n");
}

static void	ps_check_location(const std::string value)
{
	if (value.empty())
		throw std::runtime_error("Location value is empty\n");
}

void	ps_check_list(ConfigData& data)
{
	std::list<ServerNode>::iterator it;
	std::list<LocationNode>::iterator it2;

	for (it = data.serverList.begin(); it != data.serverList.end(); it++)
	{
		ps_check_server(it->server_id);
		ps_check_server_port(it->port);
		ps_check_server(it->error_page);
		ps_check_server(it->max_client_body_size);
		for (it2 = it->locationList.begin(); it2 != it->locationList.end(); it2++)
		{
			ps_check_location(it2->location);
			ps_check_location(it2->root);
			ps_check_location(it2->index);
			ps_check_location(it2->cgi_extension);
			ps_check_location(it2->autoindex);
			ps_check_location(it2->methods);
			ps_check_location(it2->redirect);
			ps_check_location(it2->directory);
			ps_check_location(it2->default_file);
			ps_check_location(it2->execute_cgi);
			ps_check_location(it2->upload_directory);
			ps_check_location(it2->directory_listening);
		}
	}
}
