/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:10:00 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/13 23:52:16 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP
# include <string>
# include <vector>
# include <iostream>
# include <sstream>
# include <stdio.h>
# include <stdlib.h>
# include <cstring>
# include <unistd.h>
# include <sys/wait.h>
# include "../includes/utils.hpp"

class Request
{
	private:
	
	public:
		std::string method; // Metodo della richiesta (GET, POST, ecc.)
		std::string path; // Percorso della richiesta (es. /index.html)
		std::string dir_path; // Percorso della richiesta (es. /)
		std::string filename; // Nome del file(es. index.html)
		std::string extension; // estensione del file (es. html)
		std::string query; // Stringa di eventuale query (es. ?id=42&name=foo)
		std::string version; // Protocollo della richiesta (es. HTTP/1.1)
		std::string host; // Host della richiesta (es. www.example.com)
		std::string ihost; // Host della richiesta in formato indirizzo IPv4
		std::string	sport;
		int			iport; // Porta della richiesta (es. 80)
		std::string user_agent;
		std::string connection; // Tipo di connessione (es. keep-alive)
		std::string accept; // Tipo di contenuto accettato (es. text/html)
		std::string accept_encoding; // Tipo di codifica accettata (es. gzip)
		std::string accept_language; // Lingua accettata (es. en-US)
		bool empty_line; // Linea vuota (separatore)
		std::string content_type; // Tipo di contenuto (solo per POST)
		std::string content_length; // Lunghezza del corpo (solo per POST)
		std::string body; // Corpo della richiesta (solo per POST)
		
		Request();
		Request(std::string& raw_str);
		~Request();
		void	getFirstLine(const std::string& raw_str);
		void	getHeaderValues(const std::string& raw_str);
		void	init_host(std::string& host_value);
};

#endif