/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 14:57:27 by gubourge          #+#    #+#             */
/*   Updated: 2016/12/15 15:40:08 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int		ft_exit(char **param, char ***env)
{
	int		i;

	env++;
	if (!param[1])
		return (0);
	i = -1;
	if (param[1][0] == '-')
		++i;
	while (param[1][++i])
		if (ft_isdigit(param[1][i]) == 0)
		{
			ft_putstr_fd("exit: Expression Syntax.\n", 2);
			return (-2);
		}
	if (param[2])
	{
		ft_putstr_fd("exit: Expression Syntax.\n", 2);
		return (-2);
	}
	return ((unsigned char)ft_atoi(param[1]));
}
