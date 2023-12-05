# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 21:19:38 by jungmiho          #+#    #+#              #
#    Updated: 2023/10/12 15:05:54 by jungmiho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

ifdef DEBUG
	CFLAGS += -g -O0
else
	CFLAGS += -O2
endif

SRCS = main.c ft_split.c handle_cmd.c handle_execve.c libft.c \
ft_strnstr.c

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
