#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/29 17:16:58 by gubourge          #+#    #+#              #
#    Updated: 2016/03/23 12:45:51 by gubourge         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

RM	= rm -f

CC = gcc

NAME = fillit

SRCS = 	main.c \
		ft_bit_reset.c \
		ft_fillit.c \
		ft_move_bit.c \
		ft_power.c \
		ft_print_bit.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all