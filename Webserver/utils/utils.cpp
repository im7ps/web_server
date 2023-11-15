/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcotza <dcotza@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 04:00:53 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/14 22:16:44 by dcotza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/utils.hpp"

// Funzione per calcolare il tempo trascorso in millisecondi
long long gettimems()
{
    timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return static_cast<long long>(currentTime.tv_sec) * 1000 + currentTime.tv_usec / 1000;
}

// Funzione per convertire un indirizzo IP numerico a una rappresentazione testuale
std::string digittoip(uint32_t numericIP)
{
    std::ostringstream oss;
    oss << ((numericIP >> 24) & 0xFF) << '.'
        << ((numericIP >> 16) & 0xFF) << '.'
        << ((numericIP >> 8) & 0xFF) << '.'
        << (numericIP & 0xFF);
    return oss.str();
}

bool is_whitespace(char chr)
{
	return (chr == ' ' || chr == '\t' || chr == '\n' || chr == '\v' || chr == '\f' || chr == '\r');
}

uint32_t	hostnametoip(const std::string& server_name, int iport)
{
	const char* hostname = server_name.c_str();

	std::stringstream ss;
	ss << iport;
	std::string sport = ss.str();
	const char* port = sport.c_str();

    struct addrinfo hints, *result, *p;
	uint32_t numericIP;
	
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    // IPv4 o IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP socket

    int status = getaddrinfo(hostname, port, &hints, &result);
    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        return (INADDR_NONE);
    }

    // Itera attraverso i risultati restituiti
    for (p = result; p != NULL; p = p->ai_next) {
        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in* ipv4 = reinterpret_cast<struct sockaddr_in*>(p->ai_addr);
			if (ipv4 == NULL)
				return (INADDR_NONE);
            numericIP = ntohl(ipv4->sin_addr.s_addr);
        }
    }

    // Rilascia la memoria allocata per i risultati
    freeaddrinfo(result);
    return numericIP;
}

// Convert a string host to a uint32_t ip address
uint32_t shosttodigit(std::string host)
{
	if (host.compare("localhost") == 0)
		return (INADDR_LOOPBACK);
	const char *cstr = host.c_str();
	int i = 0;
	int dots = 0;
	uint32_t ip = 0;
	char curr[4];
	int curr_i = 0;
	while (cstr[i])
	{
		if (cstr[i] == '.')
		{
			ip += atoi(curr) * pow(256, 3 - dots);
			dots += (cstr[i] == '.');
			curr_i = 0;
			memset(curr, 0, 4);
		} else if (isdigit(cstr[i]))
		{
			curr[curr_i] = cstr[i];
			curr_i++;
		} else
			return (INADDR_NONE);
		i++;
	}
	if (dots != 3 || ip > 4294967295 || ip < 0)
		return (INADDR_NONE);
	ip += atoi(curr);
	return (ip);
}

std::string merge_path(std::string path1, std::string path2)
{
	if (path1[path1.length() - 1] == '/')
		path1 = path1.substr(0, path1.length() - 1);
	if (path2[0] == '/')
		path2 = path2.substr(1, path2.length() - 1);
	return (path1 + "/" + path2);
}