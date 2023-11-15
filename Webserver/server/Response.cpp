/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcotza <dcotza@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:20:45 by dcotza            #+#    #+#             */
/*   Updated: 2023/11/14 23:02:40 by dcotza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Response.hpp"
#include <sstream>

Response::Response(Request *request, ServerInstance *server_instance)
{
	this->complete_response = "";
	this->body = "";
	this->request = request;
	this->file_to_serve = NULL;
	//find corresponding server_node
	this->srv_node = server_instance->get_server_node(request->host);
	//find corresponding location_node
	this->loc_node = server_instance->get_location_node(srv_node, request->dir_path);
	printf("request->dir_path: %p\n",loc_node);
	
	try {
		build_response();
	} catch (std::exception &e) {
		build_error_page();
	}
	std::stringstream iss;
	iss << this->body.length();
	this->header.content_length = iss.str();
	this->complete_response = header_to_string(&this->header) + this->body;
	printf("complete_response: \n%s\n", this->complete_response.c_str());
}

void Response::build_response()
{
	init_header();
	check_req_method();
	check_req_body_size();
	if (handle_redirection())
		return ;
	create_body();
}

void Response::init_header()
{
	this->header.status_code = "200";
	this->header.status_message = "OK";
	this->header.server = SERVER_NAME + std::string("/") + SERVER_VERSION;
	this->header.date = get_req_header_date();
	this->header.content_type = MIME_type_detector::get_MIME_type(request->extension);
	this->header.content_length = "0";
	this->header.location = "";
}

void Response::check_req_method()
{
	if (loc_node == NULL)
	{
		this->header.status_code = "404";
		this->header.status_message = "Not Found";
		throw std::exception();
	}
	printf("request->method: %s\n", request->method.c_str());
	if (is_method_allowed(loc_node->methods, request->method) == false)
	{
		this->header.status_code = "405";
		this->header.status_message = "Method Not Allowed";
		throw std::exception();
	}
}

void Response::check_req_body_size()
{
	bool is_request_content_lenght_bigger_than_body_size = request->content_length != "" && atoi(request->content_length.c_str()) > atoi(srv_node->body_size.c_str());
	bool is_request_body_bigger_than_body_size = request->body.length() > atoi(srv_node->body_size.c_str());
	if (is_request_content_lenght_bigger_than_body_size || is_request_content_lenght_bigger_than_body_size)
	{
		this->header.status_code = "413";
		this->header.status_message = "Payload Too Large";
		throw std::exception();
	}
}

std::ifstream	*Response::get_file_to_serve(std::string file_path)
{
	std::ifstream *file_to_serve = new std::ifstream(file_path.c_str());
	if (!file_to_serve)
	{
		std::cerr << "Can't open file requested!";
		return (NULL);	
	} 
	
	return (file_to_serve);
}

void	Response::build_error_page()
{
	error_page *error_page = get_error_page(srv_node->error_pages, this->header.status_code);
	// printf("error_page_path: %s\n", error_page->error_page_path.c_str());
	if (error_page != NULL && error_page->error_page_path != "")
		this->file_to_serve = get_file_to_serve(merge_path(srv_node->root, error_page->error_page_path));
	if (this->file_to_serve == NULL || this->file_to_serve->fail())
	{
		this->header.content_type = "text/html";
		this->body = "<html><head><title>" +  this->header.status_message + 
			"</title></head><body><center><h1>" + this->header.status_code + " " + this->header.status_message + 
			"</h1></center><hr><center>" + this->header.server + "</center></body></html>";
	}
}

bool	Response::handle_redirection()
{
	if (this->loc_node->redirect != "")
	{
		this->header.status_code = "301";
		this->header.status_message = "Moved Permanently";
		this->header.location = this->loc_node->redirect;
		return (true);
	}
	return (false);
}

void	Response::handle_get()
{
	if (request->filename != "") //if request is for a file
		this->file_to_serve = get_file_to_serve(merge_path(srv_node->root, request->path));
	else if (request->filename == "" && loc_node->index != "") //if request is for a directory and index is set
	{
		this->header.content_type = MIME_type_detector::get_MIME_type(loc_node->index.substr(loc_node->index.find_last_of(".") + 1));
		this->file_to_serve = get_file_to_serve(merge_path(srv_node->root, merge_path(loc_node->path, loc_node->index)));
	}
	else if (request->filename == "" && loc_node->index == "" && loc_node->autoindex) //if request is for a directory and index is not set
	{
		this->header.content_type = "text/html";
		this->body = get_dirlist(merge_path(srv_node->root, request->dir_path));
		return ;
	}
	if (this->file_to_serve == NULL || this->file_to_serve->fail())
	{
		this->header.status_code = "404";
		this->header.status_message = "Not Found";
		throw std::exception();
	}
}

void	Response::create_body()
{
	if (request->method == "get")
		handle_get();
	while (this->file_to_serve != NULL && this->file_to_serve->fail() == false && !this->file_to_serve->eof())
	{
		std::string line;
		std::getline(*this->file_to_serve, line);
		this->body += line + std::string("\n");
	}
}

int Response::send_response(int fd)
{
	std::cout << "Sending response\n";
	if (send(fd, this->complete_response.c_str(), this->complete_response.length(), 0) == -1)
	{
		std::cout << "Error sending response" << std::endl;
		return (-1);
	}
	return 0;
}

std::string Response::get_response()
{
	return complete_response;
}

Response::~Response()
{
}
