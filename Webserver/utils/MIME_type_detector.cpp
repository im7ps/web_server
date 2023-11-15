/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MIME_type_detector.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:52:26 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/12 11:28:25 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MIME_type_detector.hpp"

std::map<std::string, std::string>	MIME_type_detector::MIME_types;
int MIME_type_detector::init_mime_types()
{
	std::ifstream mime_types_file;
	mime_types_file.open(path.c_str(), std::ifstream::in);
	//parse csv and populate MIME_types map
	if (mime_types_file.is_open())
	{
		std::string line;
		//ignore first line
		getline(mime_types_file, line);
		while (getline(mime_types_file, line))
		{
			std::string key = line.substr(0, line.find(","));
			std::string value = line.substr(line.find(",") + 1, line.length());

			// std::cout << "key: " << key << " value: " << value << std::endl;
			MIME_types[key] = value;
		}
		mime_types_file.close();
		return (0);
	}
	return (1);
}

MIME_type_detector::MIME_type_detector(std::string path)
{
	int error = 0;
	this->path = path;
	if (MIME_types.size() == 0)
		error = init_mime_types();
	if (error)
		std::cout << "Error parsing or opening mime types reference file" << std::endl;
	
}

std::string MIME_type_detector::get_MIME_type(std::string extension)
{
	std::string mime_type = MIME_types[extension];
	if (mime_type.empty())
		return ("text/plain");
	return (MIME_types[extension]);
}