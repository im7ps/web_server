/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcotza <dcotza@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 02:47:51 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/14 22:04:43 by dcotza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP
# include <stdlib.h>
# include <iostream>
# include <string>
# include <string.h>
# include <math.h>
# include <stdio.h>
# include <sstream>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <netdb.h>

bool		is_whitespace(char chr);
std::string merge_path(std::string path1, std::string path2);
uint32_t	hostnametoip(const std::string& server_name, int ports);
long long	gettimems();

#endif