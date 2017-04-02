/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_oldpwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:22:43 by gubourge          #+#    #+#             */
/*   Updated: 2016/12/08 15:02:22 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"

char		*find_my(char **env, char *str, char opt)
{
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], str, ft_strlen(str)) != 0)
		++i;
	if (env[i] == NULL)
		return (NULL);
	if (opt)
		return (&env[i][ft_strlen(str)]);
	return (env[i]);
}

static int	cd_pwd_trunc(char ***env)
{
	int		i;
	char	*var_env;

	i = 0;
	if (!(var_env = find_my(*env, "PWD=", 0)))
		return (-1);
	i = ft_strlen(var_env);
	while (var_env[i] != '/')
		--i;
	var_env[i] = 0;
	return (1);
}

char		*cd_pwd_add(char *line, char **env)
{
	char	*new_pwd;
	char	*pwd;
	int		i;
	int		j;

	j = 0;
	if ((pwd = ft_strdup(find_my(env, "PWD="))) == NULL)
		return (NULL);
	if ((new_pwd = malloc((ft_strlen(pwd) +
			ft_strlen(line) + 2) * sizeof(char))) == NULL)
		return (NULL);
	new_pwd = memset(new_pwd, 0, sizeof(char));
	if (pwd)
		new_pwd = ft_strcat(new_pwd, pwd);
	new_pwd = ft_strcat(new_pwd, "/");
	i = ft_strlen(new_pwd);
	while (line[j])
		new_pwd[i++] = line[j++];
	new_pwd[i] = 0;
	return (new_pwd);
}

static int	cd_pwd_update(char *line, char ***env)
{
	char		**tab;

	if ((tab = malloc(5 * sizeof(char *))) == NULL)
		return (-1);
	tab[0] = ft_strdup("setenv");
	tab[1] = ft_strdup("PWD");
	if (line[0] == '/')
		tab[2] = ft_strdup(line);
	else if ((tab[2] = ft_strdup(cd_pwd_add(line, *env))) == NULL)
		return (-1);
	tab[3] = ft_strdup("1");
	tab[4] = NULL;
	if (tab[2] != NULL)
		ft_setenv(tab, env);
	return (1);
}

int			cd_pwd_save(char *param, char ***env)
{
	cd_pwd_to_oldpwd(param, env);
	if (ft_strcmp(param, "..") == 0)
		return (cd_pwd_trunc(env));
	else
		cd_pwd_update(line, env);
	return (1);
}
