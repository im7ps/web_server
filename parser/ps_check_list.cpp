/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_check_list.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:31:18 by stepis            #+#    #+#             */
/*   Updated: 2023/10/19 14:54:17 by stepis           ###   ########.fr       */
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

static void ps_check_listen(std::string& value)
{
	int	listen = 0;

	if (value.empty() || value == ";" || value.length() > 6)
		throw std::runtime_error("Listen value is not valid\n");

	value[value.length() - 1] = '\0'; //rimuovo il punto e virgola per mandarlo all atoi
	listen = ft_atoi(value);
	if (listen < 0 || listen > 65535)
		throw std::runtime_error("Listen value is too big or too small\n");
}

static void ps_is_empty(const std::string value)
{
	if (value.empty())
		throw std::runtime_error("Value is empty\n");
}

static void ps_check_client_size(std::string size)
{
	int client_size = 0;

	if (size.empty())
		throw std::runtime_error("Client size value is empty\n");
	size[size.length() - 1] = '\0';	//rimuovo il punto e virgola per mandarlo all atoi
	client_size = ft_atoi(size);
	if (client_size < 1 || client_size > 1048576) //valore espresso in numero di bytes (default value di nginx)
		throw std::runtime_error("Client size value is not valid\n");
}

void	ps_check_list(ConfigData& data)
{
	std::list<ServerNode>::iterator it;
	std::list<LocationNode>::iterator it2;

	for (it = data.serverList.begin(); it != data.serverList.end(); it++)
	{
		ps_check_server(it->server_id);
		ps_check_listen(it->listen);
		ps_check_client_size(it->max_client_body_size);
		ps_is_empty(it->error_page);
		for (it2 = it->locationList.begin(); it2 != it->locationList.end(); it2++)
		{
			ps_is_empty(it2->location);
			ps_is_empty(it2->index);
			ps_is_empty(it2->cgi_extension);
			ps_is_empty(it2->methods);
			ps_is_empty(it2->redirect);
			ps_is_empty(it2->directory);
			ps_is_empty(it2->default_file);
			ps_is_empty(it2->execute_cgi);
			ps_is_empty(it2->directory_listening);
		}
	}
}
