/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_ctrl_w.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 18:31:37 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/20 19:19:14 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>
#include <stdlib.h>

int			ft_key_ctrl_w(t_term *term, char **line, char c)
{
	int		tmp_pos;
	int		sv_pos;
	char	*area;

	sv_pos = term->pos_x;
	area = NULL;
	tputs(tgetstr("sc", &(area)), 1, &ft_outc);
	ft_key_alt_left(term, *line);
	tputs(tgetstr("rc", &(term->area)), 1, &ft_outc);
	if (sv_pos - term->pos_x == 0)
		return (0);
	if (term->cp)
		free(term->cp);
	if (!(term->cp = (char *)malloc(sizeof(char) * (sv_pos - term->pos_x + 1))))
		return (-1);
	ft_strncpy(term->cp, &((*line)[term->pos_x]), sv_pos - term->pos_x);
	term->cp[sv_pos - term->pos_x] = 0;
	tmp_pos = term->pos_x;
	term->pos_x = sv_pos;
	sv_pos = tmp_pos;
	while (term->pos_x > sv_pos)
		ft_key_del(term, line, c);
	return (0);
}
