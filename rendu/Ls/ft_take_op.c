/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_take_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 18:52:32 by gubourge          #+#    #+#             */
/*   Updated: 2016/10/19 15:45:50 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_take_op_bis(char *op, char *o, char av)
{
	int		k;

	k = -1;
	while (o[++k])
		if (o[k] == av)
		{
			if (*op != ft_power(2, k))
				*op += ft_power(2, k);
			return (1);
		}
	return (0);
}

int		ft_take_op(char **av, char *op)
{
	int		i;
	int		j;
	char	count;
	char	o[6];

	ft_strcpy(o, "aRltr");
	i = -1;
	while (av[++i] && av[i][0] == '-')
	{
		j = 0;
		while (av[i][++j])
		{
			count = ft_take_op_bis(op, o, av[i][j]);
			if (!count)
			{
				*op = av[i][j];
				return (-1);
			}
		}
	}
	return (0);
}

int		no_path(char **av)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (av[i])
	{
		if (av[i][0] != '-' || (av[i][0] == '-' && av[i][1] == 0))
			++count;
		i++;
	}
	if (!count)
		return (0);
	return (count);
}
