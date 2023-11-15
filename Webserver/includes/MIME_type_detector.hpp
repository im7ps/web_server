/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MIME_type_detector.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:55:39 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/12 11:28:25 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIME_TYPE_DETECTOR_HPP
# define MIME_TYPE_DETECTOR_HPP

# include <string>
# include <map>
# include <iostream>
# include <fstream>

class MIME_type_detector
{
	private:
		std::string path;
		static std::map<std::string, std::string>	MIME_types;
		int init_mime_types();
	public:
		MIME_type_detector(std::string path);
		static std::string	get_MIME_type(std::string extension);
};

#endif