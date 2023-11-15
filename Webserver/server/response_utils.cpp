/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response_utils.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:48:55 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/14 18:29:09 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Response.hpp"

bool is_method_allowed(std::list<std::string> methods, std::string method_to_find)
{
	for (std::list<std::string>::iterator it = methods.begin(); it != methods.end(); ++it)
	{
		//printf("checking method: %s\n", (*it).c_str());
		if (*it == method_to_find)
			return (true);
	}
	return (false);
}

error_page *get_error_page(std::list<error_page> error_pages, std::string error_code)
{
	for (std::list<error_page>::iterator it = error_pages.begin(); it != error_pages.end(); ++it)
	{
		if (it->error_code == error_code)
			return (&(*it));
	}
	return (NULL);
}

std::string get_dirlist(std::string path)
{
	std::string dirlist = "<html><head><title>Index of " + path + "</title></head><body><h1>Index of " + path + "</h1><hr><pre>";
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (path.c_str())) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL) {
			if (ent->d_type == DT_DIR)
				dirlist += "<a href=\"" + std::string(ent->d_name) + "/\">" + std::string(ent->d_name) + "/</a><br>";
			else
				dirlist += "<a href=\"" + std::string(ent->d_name) + "\">" + std::string(ent->d_name) + "</a><br>";
		}
		closedir (dir);
	} else {
		std::cout << "Could not open directory";
		return ("");
	}
	dirlist += "</pre><hr></body></html>";
	return (dirlist);
}


std::string header_to_string(header *header)
{
	std::string headers = HTTP_VERSION + std::string(" ") + header->status_code + std::string(" ") + header->status_message + std::string("\r\n");
	headers += std::string("Server: ") + header->server + std::string("\r\n");
	headers += std::string("Date: ") + header->date + std::string("\r\n");
	headers += std::string("Content-Type: ") + header->content_type + std::string("\r\n");
	headers += std::string("Content-Length: ") + header->content_length + std::string("\r\n");
	if (header->location != "")
		headers += std::string("Location: ") + header->location + std::string("\r\n");
	headers += std::string("\r\n");
	return (headers);
}

std::string get_req_header_date()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S %Z", timeinfo);
	std::string str(buffer);
	return (str);
}