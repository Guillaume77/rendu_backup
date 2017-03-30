/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_ctrl_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 19:21:27 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/20 19:27:28 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int			ft_key_ctrl_u(t_term *term, char **line, char c)
{
	c++;
	if ((*line)[0] == 0)
		return (0);
	if (term->cp)
		free(term->cp);
	if (!(term->cp = ft_strdup(*line)))
		return (-1);
	ft_del_all(term, *line);
	return (0);
}
