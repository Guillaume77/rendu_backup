/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_enter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 14:38:53 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/29 19:03:27 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

void		ft_freehistory(t_term *term)
{
	int		i;

	i = -1;
	while (++i < MAX_HISTORY)
	{
		if (term->history[i])
			free(term->history[i]);
		if (term->tmp_history[i])
			free(term->tmp_history[i]);
	}
	if (term->tmp_history[i])
		free(term->tmp_history[i]);
}

int			ft_put_history(t_term *term, char *line)
{
	int		i;
	char	*tmp[MAX_HISTORY];

	i = -1;
	while (++i < MAX_HISTORY)
		tmp[i] = term->history[i];
	i = -1;
	while (++i < MAX_HISTORY)
	{
		if (i == 0)
		{
			if (!(term->history[i] = ft_strdup(line)))
				return (-1);
		}
		else
			term->history[i] = tmp[i - 1];
	}
	if (tmp[i - 1])
		free(tmp[i - 1]);
	return (0);
}

int			ft_cp_history(t_term *term)
{
	int		i;

	i = -1;
	while (++i < MAX_HISTORY)
	{
		if (term->tmp_history[i + 1])
			free(term->tmp_history[i + 1]);
		term->tmp_history[i + 1] = ft_strdup(term->history[i]);
	}
	return (0);
}

int			ft_key_enter(t_term *term, char **line, char c)
{
	c++;
	line++;
	ft_putchar('\n');
	term->pos_x = 0;
	term->i_hsty = 0;
	return (1);
}
