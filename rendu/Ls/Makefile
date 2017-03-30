#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/29 17:16:58 by gubourge          #+#    #+#              #
#    Updated: 2016/11/07 13:50:37 by gubourge         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

RM	= rm -f

CC = gcc

NAME = ft_ls

SRCS =	ft_ls.c \
		ft_strcmp.c \
		ft_strcmp_modify.c \
		ft_strcmp_r.c \
		ft_strcmp_rt.c \
		ft_strcmp_t.c \
		ft_strcpy.c \
		ft_strcat.c \
		ft_strlen.c \
		ft_advanced_sort_wordtab.c \
		ft_n_a.c \
		ft_strdup.c \
		ft_take_op.c \
		ft_power.c \
		ft_itoa.c \
		ft_print_funcs.c \
		ft_print_funcs_bis.c \
		ft_init_func_ptr.c \
		print_list_l.c \
		ft_putnbr.c \
		list_funcs/ft_create_elem.c \
		list_funcs/ft_list_push_back.c \
		list_funcs/ft_list_sort.c \
		list_funcs/ft_list_reverse.c \
		list_funcs/ft_list_remove_if.c \
		list_funcs/ft_free_list.c \

CFLAGS = -Wall -Wextra -Werror -I .

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
