# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stepis <stepis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/01 19:04:12 by sgerace           #+#    #+#              #
#    Updated: 2023/10/16 15:54:24 by stepis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = web_server

USER = sgerace

CXXFLAGS = -g -std=c++98 #-Wall -Wextra -Werror 

SRCS = 	./main/main.cpp \
		./main/main_utils.cpp \
		./parser/ps_curlyb.cpp \
		./utils/ft_trim.cpp \
		./utils/ft_itos.cpp \

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