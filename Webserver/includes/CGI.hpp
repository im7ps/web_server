/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>              +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:58:31 by sgerace            #+#    #+#             */
/*   Updated: 2023/11/12 11:25:46 by sgerace           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

#include "../includes/Request.hpp"

class CGI
{
	private:
	public:
		std::string path_info;

		CGI();
		~CGI();
		int	exec_cgi(Request& request);
		void get_file_path(Request &request);
};

#endif