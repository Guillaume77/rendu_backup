/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_left_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 14:31:37 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/13 18:57:28 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

void		ft_key_right(t_term *term, char *line)
{
	struct winsize	argp;
	int				tmp_pos;

	if ((ioctl(0, TIOCGWINSZ, &argp)) == -1)
		return ;
	term->pos_y = (term->pos_x + ft_strlen(PROMPT)) / argp.ws_col;
	tmp_pos = (term->pos_x + 1) + ft_strlen(PROMPT) - (term->pos_y * argp.ws_col);
	ft_cursor_right(term, tmp_pos, argp.ws_col, ft_strlen(line));
}

void		ft_key_left(t_term *term, char *line)
{
	struct winsize	argp;
	int				tmp_pos;

	if ((ioctl(0, TIOCGWINSZ, &argp)) == -1)
		return ;
	term->pos_y = (term->pos_x + ft_strlen(PROMPT)) / argp.ws_col;
	tmp_pos = (term->pos_x + 1) + ft_strlen(PROMPT) - (term->pos_y * argp.ws_col);
	ft_cursor_left(term, tmp_pos, argp.ws_col, ft_strlen(line));
}
