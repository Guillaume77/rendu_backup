/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_alt_up_down.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:03:48 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/31 15:54:18 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>
#include <sys/ioctl.h>

void		ft_key_alt_up(t_term *term, char *line)
{
	struct winsize	argp;

	if ((ioctl(0, TIOCGWINSZ, &argp)) == -1)
		return ;
	term->pos_y = (term->pos_x + ft_strlen(term->prompt)) / argp.ws_col;
	if (term->pos_y - 1 <= 0)
	{
		if (term->pos_y - 1 == 0)
			{
				tputs(tgetstr("sr", &(term->area)), 1, &ft_outc);
				term->pos_x -= argp.ws_col;
				if (term->pos_x < ((int)ft_strlen(term->prompt) - 1))
				{
					ft_cursor_more_right(term, ft_strlen(line));
					ft_cursor_more_left(term);
				}
			}
	}
	else
	{
		tputs(tgetstr("sr", &(term->area)), 1, &ft_outc);
		term->pos_x -= argp.ws_col;
	}
}

void		ft_key_alt_down(t_term *term, char *line)
{
	struct winsize	argp;
	int				tmp_pos;

	if ((ioctl(0, TIOCGWINSZ, &argp)) == -1)
		return ;
	term->pos_y = (term->pos_x + ft_strlen(term->prompt)) / argp.ws_col;
	tmp_pos = term->pos_x + argp.ws_col;
	while (term->pos_x < tmp_pos && line[term->pos_x])
		ft_cursor_right(term, (term->pos_x + 1) + ft_strlen(term->prompt) - (term->pos_y * argp.ws_col), argp.ws_col, ft_strlen(line));
}
