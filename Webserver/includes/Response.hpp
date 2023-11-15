/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcotza <dcotza@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:48:22 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/14 18:18:19 by dcotza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP
# include "ServerInstance.hpp"
# include "Request.hpp"
# include "MIME_type_detector.hpp"

# define HTTP_VERSION "HTTP/1.1"
# define SERVER_NAME "webserv"
# define SERVER_VERSION "1.0"

typedef struct header_t
{
	std::string	status_code;
	std::string status_message;
	std::string server;
	std::string date;
	std::string content_type;
	std::string content_length;
	std::string location;
} header;

class Response
{
private:
	header_t		header;
	std::string 	body;
	std::ifstream	*file_to_serve;

	std::string 	complete_response;

	Request *request;
	server_node *srv_node;
	location_node *loc_node;

	void 			check_req_method();
	void			check_req_body_size();
	void			init_header();
	void 			create_body();
	bool			handle_redirection();
	void			handle_get();
	void			build_error_page();
	void			build_response();

	std::ifstream  *get_file_to_serve(std::string path);

public:
	std::string get_response();
	int			send_response(int fd);
	Response(Request *request, ServerInstance *server_instance);
	~Response();
};

bool is_method_allowed(std::list<std::string> methods, std::string method_to_find);
error_page *get_error_page(std::list<error_page> error_pages, std::string error_code);
std::string get_dirlist(std::string path);
std::string header_to_string(header *header);
std::string  get_req_header_date();




#endif