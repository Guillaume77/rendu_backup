/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:21:39 by gubourge          #+#    #+#             */
/*   Updated: 2017/04/02 18:02:33 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

int		env_find_opt(t_env *env_built, char **param, int *i, char ***env)
{
	if (!ft_strcmp(param[*i], "-i"))
	{
		ft_freetab(env_cp, ft_tablen(env_cp));
		*env = NULL;
	}
	else if (!ft_strcmp(param[*i], "-u"))
	{
		if (!(env_u(env, env_built, &param[*i + 1], i)))
			return (0);
	}
	else if (!ft_strcmp(param[*i], "-P"))
	{
		if (!(env_p(&param[*i + 1], env_built, i)))
			return (0);
	}
	else
	{
		if (!(env_p_bis(env_built, &param[*i], env_built->opt_p)))
			return (0);
		exec_cmd(&param[*i], env);
		return (0);
	}
	return (1);
}

void	env_parse_param(char **param, char ***env)
{
	t_env	env_built;
	int		i;

	env_built.tab[0] = NULL;
	env_built.tab[1] = NULL;
	env_built.tab[2] = NULL;
	env_built.tmp = NULL;
	env_built.opt_p = 0;
	i = -1;
	while (param[++i])
		if (!(env_find_opt(&env_built, param, &i, env)))
			return ;
	env_built.tab[1] = NULL;
	ft_env(env_built.tab, env);
}

int		ft_env(char **param, char ***env)
{
	int		i;
	char	**env_cp;

	i = -1;
	if (!param[1])
	{
		if (*env)
			while ((*env)[++i])
			{
				ft_putstr((*env)[i]);
				ft_putchar('\n');
			}
	}
	else
	{
		if (cp_env(&env_cp, *env) == -1)
			return (0);
		env_parse_param(&param[1], &env_cp);
		ft_freetab(env_cp, ft_tablen(env_cp));
	}
	return (1);
}
