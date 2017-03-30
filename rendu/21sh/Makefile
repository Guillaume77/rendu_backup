#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/29 17:16:58 by gubourge          #+#    #+#              #
#    Updated: 2017/03/29 18:12:27 by gubourge         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

LIBFT = Libft/

LIBFT_NAME = Libft/libft.a

NAME = minishell

INCLUDE = -I includes/

LIB_TERM = -ltermcap

SRCS_I_O_OPERATORS = i_o_operators/double_redirection.c \
					 i_o_operators/double_redirection_gauche.c \
					 i_o_operators/pipe.c \
					 i_o_operators/redirection.c \
					 i_o_operators/redirection_gauche.c \
					 i_o_operators/semi_colon.c \
					 i_o_operators/find_last_cmd.c \

SRCS_BUILT_IN =	built_in/ft_echo.c \
				built_in/ft_cd.c \
				built_in/ft_cd_transfert.c \
				built_in/ft_setenv.c \
				built_in/ft_unsetenv.c \
				built_in/ft_env.c \
				built_in/ft_env_opt.c \
				built_in/ft_exit.c \

SRCS_KEY_EVENT = key_event/ft_cursor_motion.c \
				 key_event/ft_key_alt_left_right.c \
				 key_event/ft_key_alt_up_down.c \
				 key_event/ft_key_del.c \
				 key_event/ft_key_enter.c \
				 key_event/ft_key_event.c \
				 key_event/ft_key_home_end.c \
				 key_event/ft_key_left_right.c \
				 key_event/ft_key_up_down.c \
				 key_event/ft_key_ctrl_d.c \
				 key_event/ft_key_ctrl_c.c \
				 key_event/ft_key_ctrl_k.c \
				 key_event/ft_key_ctrl_y.c \
				 key_event/ft_key_ctrl_w.c \
				 key_event/ft_key_ctrl_u.c \

SRCS = 	$(SRCS_BUILT_IN) \
		$(SRCS_KEY_EVENT) \
		$(SRCS_I_O_OPERATORS) \
		main.c \
		ft_parse.c \
		ft_ultimate_strdup.c \
		ft_minishell.c \
		ft_find_cmd.c \
		ft_command_line.c \
		ft_find_built_in.c \
		ft_shlvl.c \
		ft_termcaps.c \
		ft_init_termios.c \
		ft_init_func_ptr.c \


OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror $(INCLUDE)

$(NAME): $(OBJS)
	@$(MAKE) -s -C $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT_NAME) $(LIB_TERM)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	@$(MAKE) -s -C $(LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT) fclean

re: fclean all