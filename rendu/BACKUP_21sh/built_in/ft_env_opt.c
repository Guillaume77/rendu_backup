/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:35:04 by gubourge          #+#    #+#             */
/*   Updated: 2016/12/08 16:28:10 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

int		env_u(char ***env, t_env *env_built, char **param, int *i)
{
	if (!(*param))
	{
		ft_putstr_fd("env: option requires an argument -- u\n", 2);
		ft_putstr_fd("usage: env [-i] [-P utilpath] [-u name] ", 2);
		ft_putstr_fd("[name=value ...] [utility [argument ...]]\n", 2);
		return (0);
	}
	if (*env)
	{
		env_built->tab[1] = ft_strdup(*param);
		ft_unsetenv(env_built->tab, env);
		free(env_built->tab[1]);
		env_built->tab[1] = NULL;
	}
	(*i)++;
	return (1);
}

int		env_p(char **param, t_env *env_built, int *i)
{
	if (!(*param))
	{
		ft_putstr_fd("env: option requires an argument -- P\n", 2);
		ft_putstr_fd("usage: env [-i] [-P utilpath] [-u name] ", 2);
		ft_putstr_fd("[name=value ...] [utility [argument ...]]\n", 2);
		return (0);
	}
	env_built->opt_p = 1;
	env_built->tmp = ft_strdup(*param);
	(*i)++;
	return (1);
}

int		env_p_bis(t_env *env_built, char **param, char opt_p)
{
	if (opt_p)
	{
		if (!(env_built->tab[0] = (char *)malloc(sizeof(char) *
			(ft_strlen(env_built->tmp) + ft_strlen(*param) + 2))))
			return (0);
		if (!ft_strcpy(env_built->tab[0], env_built->tmp))
			return (0);
		if (env_built->tab[0][ft_strlen(env_built->tab[0]) - 1] != '/')
			ft_strcat(env_built->tab[0], "/");
		ft_strcat(env_built->tab[0], *param);
		if (access(env_built->tab[0], F_OK | X_OK) == -1)
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(*param, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (0);
		}
		free(*param);
		free(env_built->tmp);
		env_built->tmp = NULL;
		*param = env_built->tab[0];
	}
	return (1);
}
