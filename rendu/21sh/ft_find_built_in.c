/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 12:14:58 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/29 18:24:08 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_built_in(t_builtin *builtin, char **param, char ***env)
{
	int		i;

	i = 0;
	while (builtin->tab_built[i])
	{
		if (ft_strcmp(param[0], builtin->tab_built[i]) == 0)
			return ((builtin->tab_func[i](param, env)));
		i++;
	}
	return (-2);
}
