#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/29 17:16:58 by gubourge          #+#    #+#              #
#    Updated: 2017/01/12 16:20:45 by gubourge         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

LIBFT = Libft/

LIBFT_NAME = Libft/libft.a

NAME = minishell

INCLUDE = -I includes/

SRCS_BUILT_IN = built_in/ft_echo.c \
				built_in/ft_cd.c \
				built_in/ft_cd_transfert.c \
				built_in/ft_setenv.c \
				built_in/ft_unsetenv.c \
				built_in/ft_env.c \
				built_in/ft_env_opt.c \
				built_in/ft_exit.c \

SRCS = 	main.c \
		ft_parse.c \
		ft_minishell.c \
		ft_find_cmd.c \
		ft_find_built_in.c \
		ft_shlvl.c \
		$(SRCS_BUILT_IN)

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror $(INCLUDE)

$(NAME): $(OBJS)
	@$(MAKE) -s -C $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT_NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	@$(MAKE) -s -C $(LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT) fclean

re: fclean all