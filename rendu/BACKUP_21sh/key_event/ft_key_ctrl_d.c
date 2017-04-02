/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_ctrl_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 14:33:25 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/31 17:36:04 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int			ft_key_ctrl_d(t_term *term, char **line, char c)
{
	if (ft_strcmp(term->prompt, PROMPT_HEREDOC) == 0)
		return (0);
	c++;
	if ((*line)[0] == 0)
	{
		free(*line);
		return (2);
	}
	return (0);
}
