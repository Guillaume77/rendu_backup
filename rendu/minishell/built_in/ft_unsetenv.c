/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 18:00:30 by gubourge          #+#    #+#             */
/*   Updated: 2016/11/21 18:20:46 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	ft_del_to_env(char *param, char ***env)
{
	int		i;
	int		j;
	char	**tmp;
	char	**env_tmp;

	if (!(tmp = find_my(env, param)))
		return ;
	i = 0;
	j = 0;
	if (!ft_tablen(*env))
		return ;
	if (!(env_tmp = (char **)malloc(sizeof(char *) * (ft_tablen((*env))))))
		return ;
	while ((*env)[i])
	{
		if (ft_strcmp((*env)[i], *tmp) != 0)
			env_tmp[j++] = (*env)[i];
		i++;
	}
	env_tmp[j] = NULL;
	free(*tmp);
	free((*env));
	(*env) = env_tmp;
}

int		ft_unsetenv(char **param, char ***env)
{
	int		i;

	if (!param[1])
	{
		ft_putstr_fd("unsetenv: Too few arguments.\n", 2);
		return (-1);
	}
	i = 0;
	while (param[++i])
		if (ft_str_is_alpha(param[i]))
			ft_del_to_env(param[i], env);
	return (1);
}
