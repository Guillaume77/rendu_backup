/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:49:00 by gubourge          #+#    #+#             */
/*   Updated: 2016/11/29 16:15:58 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

char	**find_my(char ***env, char *str)
{
	int		i;

	if (!env)
		return (NULL);
	if (!(*env))
		return (NULL);
	i = -1;
	while ((*env)[++i])
		if (ft_strncmp((*env)[i], str, ft_strlen(str)) == 0 &&
			(*env)[i][ft_strlen(str)] == '=')
			return (&(*env)[i]);
	return (NULL);
}

int		ft_str_is_alpha(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '_' && !(str[i] >= '0' && str[i] <= '9'))
			if (!ft_isalpha(str[i]))
				return (0);
		i++;
	}
	return (1);
}

char	*ft_create_var_env(char *name_var, char *content_var)
{
	char	*var_env;

	if (!(var_env = (char *)malloc(sizeof(char) *
		(ft_strlen(name_var) + ft_strlen(content_var) + 2))))
		return (NULL);
	ft_strcpy(var_env, name_var);
	ft_strcat(var_env, "=");
	if (content_var)
		ft_strcat(var_env, content_var);
	return (var_env);
}

int		ft_put_to_env(char *var_env, char *param, char ***env)
{
	int		i;
	char	**tmp;
	char	**env_tmp;

	if ((tmp = find_my(env, param)))
	{
		free(*tmp);
		*tmp = var_env;
		return (-1);
	}
	i = 0;
	if (!(env_tmp = (char **)malloc(sizeof(char *) * (ft_tablen((*env)) + 2))))
		return (-1);
	while ((*env)[i])
	{
		env_tmp[i] = (*env)[i];
		i++;
	}
	env_tmp[i] = var_env;
	env_tmp[i + 1] = NULL;
	free((*env));
	(*env) = env_tmp;
	return (1);
}

int		ft_setenv(char **param, char ***env)
{
	char	*var_env;

	if (!param[1])
		return (ft_env(param, env));
	if (!(ft_str_is_alpha(param[1])))
	{
		ft_putstr_fd(
			"setenv: Variable name must contain alphanumeric characters.\n", 2);
		return (-1);
	}
	if (ft_tablen(param) > 3)
	{
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
		return (-1);
	}
	if (!(var_env = ft_create_var_env(param[1], param[2])))
		return (-1);
	return (ft_put_to_env(var_env, param[1], env));
}
