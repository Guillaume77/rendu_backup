/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:00:13 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/20 18:54:49 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>
#include <stdlib.h>

int			ft_key_del(t_term *term, char **line, char c)
{
	char	*tmp;

	if (term->pos_x > 0)
	{
		ft_key_left(term, *line);
		term->res = tgetstr("sc", &(term->area));
		tputs(term->res, 1, &ft_outc);
		(*line)[term->pos_x] = 0;
		tputs(&((*line)[term->pos_x + 1]), 1, &ft_outc);
		tputs(" ", 1, &ft_outc);
		tmp = ft_strjoin(*line, &((*line)[term->pos_x + 1]));
		ft_strcpy(*line, tmp);
		free(tmp);
		term->res = tgetstr("rc", &(term->area));
		tputs(term->res, 1, &ft_outc);
	}
	c++;
	return (0);
}
