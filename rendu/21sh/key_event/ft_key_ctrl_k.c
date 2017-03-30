/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_ctrl_k.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 16:47:46 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/20 16:28:55 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>
#include <stdlib.h>
#include <limits.h>

int			ft_del_all_at_pos(t_term *term, char *line)
{
	int		cpt;
	int		tmp_pos_x;

	cpt = 0;
	tmp_pos_x = term->pos_x;
	tputs(tgetstr("sc", &(term->area)), 1, &ft_outc);
	ft_key_end(term, line);
	while (line[term->pos_x] != 0)
	{
		if (++cpt == INT_MAX)
			return (-1);
		ft_key_alt_down(term, line);
	}
	ft_key_home(term, line);
	while (cpt > 0)
	{
		tputs(tgetstr("cd", &(term->area)), 1, &ft_outc);
		ft_key_alt_up(term, line);
		cpt--;
	}
	tputs(tgetstr("rc", &(term->area)), 1, &ft_outc);
	tputs(tgetstr("ce", &(term->area)), 1, &ft_outc);
	term->pos_x = tmp_pos_x;
	return (0);
}

int			ft_key_ctrl_k(t_term *term, char **line, char c)
{
	char	*tmp;

	c++;
	if ((*line)[term->pos_x] == 0)
		return (0);
	if (term->cp)
		free(term->cp);
	term->cp = ft_strdup(&((*line)[term->pos_x]));
	if (ft_del_all_at_pos(term, *line) == -1)
		return (-1);
	if (!(tmp = (char *)malloc(sizeof(char) *
		(LINE_SIZE * (ft_strlen(*line) / LINE_SIZE + 1)))))
		return (-1);
	(*line)[term->pos_x] = 0;
	ft_strcpy(tmp, *line);
	free(*line);
	*line = tmp;
	return (0);
}
