/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_ctrl_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 15:40:29 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/20 16:05:37 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int			ft_key_ctrl_c(t_term *term, char **line, char c)
{
	int		y;

	y = term->pos_y;
	c++;
	term->i_hsty = 0;
	ft_key_end(term, *line);
	while ((*line)[term->pos_x] != 0)
		ft_key_alt_down(term, *line);
	ft_putchar('\n');
	(*line)[0] = 0;
	return (1);
}
