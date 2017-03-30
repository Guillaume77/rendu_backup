/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_up_down.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:01:50 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/20 19:26:47 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>
#include <sys/ioctl.h>
#include <stdlib.h>

void		ft_del_all(t_term *term, char *line)
{
	struct winsize	argp;

	if ((ioctl(0, TIOCGWINSZ, &argp)) == -1)
		return ;
	term->pos_y = (term->pos_x + ft_strlen(PROMPT)) / argp.ws_col;
	while (term->pos_y > 0)
		ft_key_alt_up(term, line);
	ft_cursor_more_left(term);
	tputs(tgetstr("cd", &(term->area)), 1, &ft_outc);
	ft_bzero(line, ft_strlen(line));
}

void		ft_key_up(t_term *term, char *line)
{
	int		i;

	if (term->i_hsty + 1 >= MAX_HISTORY + 1)
		return ;
	if (!term->tmp_history[term->i_hsty + 1])
		return ;
	if (term->tmp_history[term->i_hsty])
		free(term->tmp_history[term->i_hsty]);
	term->tmp_history[term->i_hsty] = ft_strdup(line);
	i = 0;
	ft_del_all(term, line);
	(term->i_hsty)++;
	while (term->tmp_history[term->i_hsty][i])
	{
		ft_key(term, &line, term->tmp_history[term->i_hsty][i]);
		i++;
	}
}

void		ft_key_down(t_term *term, char *line)
{
	int		i;

	if (term->i_hsty - 1 < 0)
		return ;
	if (term->tmp_history[term->i_hsty])
		free(term->tmp_history[term->i_hsty]);
	term->tmp_history[term->i_hsty] = ft_strdup(line);
	i = 0;
	ft_del_all(term, line);
	(term->i_hsty)--;
	while (term->tmp_history[term->i_hsty][i])
	{
		ft_key(term, &line, term->tmp_history[term->i_hsty][i]);
		i++;
	}
}
