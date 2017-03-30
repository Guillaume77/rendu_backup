/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_ctrl_y.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 17:09:52 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/20 17:10:02 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int		ft_key_ctrl_y(t_term *term, char **line, char c)
{
	int	i;

	c++;
	if (!term->cp)
		return (0);
	i = -1;
	
	while (term->cp[++i])
		if (ft_key(term, line, term->cp[i]) == -1)
			return (-1);
	return (0);
}
