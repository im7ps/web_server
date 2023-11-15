# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcotza <dcotza@student.42roma.it>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 02:14:02 by dcotza            #+#    #+#              #
#    Updated: 2023/11/12 18:32:31 by dcotza           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = web_server

CXXFLAGS = -g -std=c++98 #-Wall -Wextra -Werror 

SRCS = 	main.cpp parser/ServerConfig.cpp parser/parser_utils.cpp utils/utils.cpp server/ServerInstance.cpp server/ClientInstance.cpp \
		server/Request.cpp server/Response.cpp CGI/CGI.cpp utils/MIME_type_detector.cpp server/response_utils.cpp

OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJS)
	c++ $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	c++ $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

update_docker:
	sudo docker build -t web_server .
	sudo docker run -it -p 8080:8080 web_server