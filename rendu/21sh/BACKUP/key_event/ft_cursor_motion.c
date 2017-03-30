/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_motion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:18:55 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/09 18:25:49 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <termcap.h>
#include <term.h>
#include <sys/ioctl.h>

void		ft_cursor_left(t_term *term, int tmp_pos, int len_col, int len_line)
{
	if (term->pos_x > 0)
	{
		if (tmp_pos == 1)
		{
			term->res = tgetstr("sr", &(term->area));
			tputs(term->res, 1, &ft_outc);
			term->pos_x -= len_col;
			ft_cursor_more_right(term, len_line);
		}
		else
		{
			(term->pos_x)--;
			term->res = tgetstr("le", &(term->area));
			tputs(term->res, 1, &ft_outc);
		}
	}
}

void		ft_cursor_right(t_term *term, int tmp_pos, int len_col, int len_line)
{
	if (term->pos_x < len_line)
	{
		if (tmp_pos == len_col)
		{
			term->res = tgetstr("sf", &(term->area));
			tputs(term->res, 1, &ft_outc);
			ft_putchar('\r');
		}
		else
		{
			term->res = tgetstr("nd", &(term->area));
			tputs(term->res, 1, &ft_outc);
		}
		(term->pos_x)++;
	}
}

void		ft_cursor_more_right(t_term *term, int len_line)
{
	struct winsize	argp;
	int				tmp_pos;

	if ((ioctl(0, TIOCGWINSZ, &argp)) == -1)
		return ;
	term->pos_y = (term->pos_x + ft_strlen(PROMPT)) / argp.ws_col;
	tmp_pos = (term->pos_x + 1) + ft_strlen(PROMPT) - (term->pos_y * argp.ws_col);
	while ((tmp_pos < argp.ws_col) && (term->pos_x < len_line))
	{
		term->res = tgetstr("nd", &(term->area));
		tputs(term->res, 1, &ft_outc);
		(term->pos_x)++;
		(tmp_pos)++;
	}
}

void		ft_cursor_more_left(t_term *term)
{
	struct winsize	argp;
	int				tmp_pos;

	if ((ioctl(0, TIOCGWINSZ, &argp)) == -1)
		return ;
	term->pos_y = (term->pos_x + ft_strlen(PROMPT)) / argp.ws_col;
	tmp_pos = (term->pos_x + 1) + ft_strlen(PROMPT) - (term->pos_y * argp.ws_col);
	if (term->pos_y > 0)
		tmp_pos += (int)ft_strlen(PROMPT);
	while (tmp_pos > (1 + (int)ft_strlen(PROMPT)))
	{
		term->res = tgetstr("le", &(term->area));
		tputs(term->res, 1, &ft_outc);
		(term->pos_x)--;
		(tmp_pos)--;
	}
}
