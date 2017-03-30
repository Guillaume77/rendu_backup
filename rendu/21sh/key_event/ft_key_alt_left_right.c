/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_alt_left_right.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 14:34:33 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/20 18:48:30 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>

static void		ft_key_check_left(void (func)(t_term *term, char *line),
							t_term *term, char *line, int *i)
{
	func(term, line);
	(*i)--;
}

void			ft_key_alt_left(t_term *term, char *line)
{
	int		i;
	char	word;
	int		sv_pos_x;

	i = term->pos_x;
	sv_pos_x = term->pos_x;
	word = 0;
	tputs(tgetstr("sc", &(term->area)), 1, &ft_outc);
	if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && i > 0)
		ft_key_check_left(&ft_key_left, term, line, &i);
	while ((line[i] == ' ' || line[i] == '\t' || line[i] == '\n') && i > 0)
		ft_key_check_left(&ft_key_left, term, line, &i);
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && i > 0)
	{
		ft_key_check_left(&ft_key_left, term, line, &i);
		word = 1;
	}
	if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		ft_key_right(term, line);
	if (!word)
	{
		tputs(tgetstr("rc", &(term->area)), 1, &ft_outc);
		term->pos_x = sv_pos_x;
	}
}

void			ft_key_alt_right(t_term *term, char *line)
{
	int		i;
	char	word;
	int		sv_pos_x;

	i = term->pos_x;
	sv_pos_x = term->pos_x;
	word = 0;
	tputs(tgetstr("sc", &(term->area)), 1, &ft_outc);
	while ((line[i] == ' ' || line[i] == '\t' || line[i] == '\n') && line[i])
	{
		ft_key_right(term, line);
		i++;
	}
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i])
	{
		ft_key_right(term, line);
		i++;
		word = 1;
	}
	if (!word)
	{
		tputs(tgetstr("rc", &(term->area)), 1, &ft_outc);
		term->pos_x = sv_pos_x;
	}
}
