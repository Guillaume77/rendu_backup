/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_bis2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:11:12 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/01 17:32:29 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <term.h>
#include <stdlib.h>
#include <sys/ioctl.h>

void		ft_key_alt_left(t_term *term, char *line, char c)
{
}

void		ft_key_alt_right(t_term *term, char *line, char c)
{
}

void		ft_key_home(t_term *term, char *line, char c)
{
	struct winsize	argp;
	int				tmp_pos;

	if ((ioctl(0, TIOCGWINSZ, &argp)) == -1)
		return ;
	term->pos_y = term->pos_x /*+ ft_strlen(PROMPT)*/ / argp.ws_col;
	tmp_pos = (term->pos_x + 1) /*+ ft_strlen(PROMPT)*/ - (term->pos_y * argp.ws_col);
	while (tmp_pos > 1)
	{
		term->res = tgetstr("le", &(term->area));
		tputs(term->res, 1, &ft_outc);
		(term->pos_x)--;
		(tmp_pos)--;
	}
}

void		ft_key_end(t_term *term, char *line, char c)
{
	ft_key_more_right(term, line, c);
}
