/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 15:23:37 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/01 17:12:36 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <term.h>
#include <stdlib.h>

void		ft_key_del(t_term *term, char *line, char c)
{
	char	*tmp;

	if (term->pos_x > 0)
	{
		ft_key_left(term, line, c);
		term->res = tgetstr("sc", &(term->area));
		tputs(term->res, 1, &ft_outc);
		line[term->pos_x] = 0;
		tputs(&line[term->pos_x + 1], 1, &ft_outc);
		tputs(" ", 1, &ft_outc);
		tmp = ft_strjoin(line, &line[term->pos_x + 1]);
		ft_strcpy(line, tmp);
		free(tmp);
		term->res = tgetstr("rc", &(term->area));
		tputs(term->res, 1, &ft_outc);
	}
}

void		ft_key_up(t_term *term, char *line, char c)
{
	tputs(tgetstr("ce", &(term->area)), 1, &ft_outc);
}

void		ft_key_down(t_term *term, char *line, char c)
{
}

void		ft_ctrl_d(t_term *term, char *line, char c)
{
}

void		ft_nothing(t_term *term, char *line, char c)
{}
