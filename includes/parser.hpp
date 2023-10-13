/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:30:26 by stepis            #+#    #+#             */
/*   Updated: 2023/10/13 17:18:38 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

#include "libraries.hpp"

#define ELEM_NUM 13

class Required {
    private:
		std::string attributes[13];
    public:
        Required();
        ~Required();
		const std::string* getAttributes();
};

bool	ps_create_map(const std::string path, std::vector<std::pair<std::string, std::string> > &configMap);
void	ps_create_map2(std::ifstream& confFile, std::vector<std::pair<std::string, std::string> > &congifMap);
int		ps_check_map(std::vector<std::pair<std::string, std::string> > &configMap);
int		ps_router(std::vector<std::pair<std::string, std::string> >::iterator it, Required& Required);
void	ps_check_server(std::string value);
void	ps_check_location(std::string value);
int		ps_check_curlyb(std::string line);
void	ft_trim(std::string& str);


#endif