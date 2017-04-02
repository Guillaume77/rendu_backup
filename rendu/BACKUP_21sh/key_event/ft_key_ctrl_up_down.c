/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_ctrl_up_down.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:04:39 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/31 15:54:56 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>
#include <sys/ioctl.h>

void		ft_key_ctrl_up(t_term *term, char *line)
{
	struct winsize	argp;
	int				tmp_pos_x;
	int				tmp_pos_y;

	if ((ioctl(0, TIOCGWINSZ, &argp)) == -1)
		return ;
	term->pos_y = (term->pos_x + ft_strlen(term->prompt)) / argp.ws_col;
	tmp_pos_y = term->pos_y;
	tmp_pos_x = (term->pos_x + 1) + ft_strlen(term->prompt) - (term->pos_y * argp.ws_col);
	while (tmp_pos_x < line_len)
		ft_cursor_right(term, 
	while (tmp_pos_y >= 0)
	{
		ft_cursor_more_left(term);
		tputs(tgetstr("ce", &(term->area)), 1, &ft_outc);
		tmp_pos_x = (term->pos_x + 1) + ft_strlen(term->prompt) - (term->pos_y * argp.ws_col);
		ft_cursor_left(term, tmp_pos_x, argp.ws_col, ft_strlen(line));
		tmp_pos_y--;
	}
/*	ft_cursor_more_left(term);
	ft_cursor_more_left(term);
	tputs(tgetstr("ce", &(term->area)), 1, &ft_outc);
	ft_putstr_fd(term->prompt, 1);
*/	ft_bzero(line, ft_strlen(line));
}

void		ft_key_ctrl_down(t_term *term, char *line)
{
	line++;
	term++;
}
