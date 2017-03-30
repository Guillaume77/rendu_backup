/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 12:41:35 by gubourge          #+#    #+#             */
/*   Updated: 2016/11/09 16:50:23 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **param, char ***env)
{
	int		i;
	int		op;

	i = 1;
	op = 0;
	env++;
	while (param[i])
	{
		if (ft_strcmp(param[i], "-n") == 0)
		{
			op++;
			i++;
		}
		else
		{
			ft_putstr(param[i]);
			i++;
			if (param[i])
				ft_putchar(' ');
		}
	}
	if (!op)
		ft_putchar('\n');
	return (1);
}
