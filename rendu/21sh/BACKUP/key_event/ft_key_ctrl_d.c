/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_ctrl_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 14:33:25 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/30 18:36:57 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int			ft_key_ctrl_d(t_term *term, char **line, char c)
{
	term++;
	c++;
	if ((*line)[0] == 0)
	{
		free(*line);
		return (2);
	}
	return (0);
}
