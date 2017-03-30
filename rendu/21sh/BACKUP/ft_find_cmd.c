/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 15:57:38 by gubourge          #+#    #+#             */
/*   Updated: 2016/11/22 17:20:58 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

char	*find_var_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

int		create_absolute_path(char *find, char ***tab_path)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*tab_path)[i])
	{
		if (!(tmp = (char *)malloc(sizeof(char) *
			(ft_strlen((*tab_path)[i]) + ft_strlen(find) + 2))))
			return (-1);
		ft_strcpy(tmp, (*tab_path)[i]);
		free((*tab_path)[i]);
		ft_strcat(tmp, "/");
		ft_strcat(tmp, find);
		(*tab_path)[i] = tmp;
		i++;
	}
	return (0);
}

char	*is_access_path(char **tab_path)
{
	int		i;

	i = 0;
	while (tab_path[i])
	{
		if ((access(tab_path[i], F_OK | X_OK)) == 0)
			return (ft_strdup(tab_path[i]));
		i++;
	}
	return (NULL);
}

char	*is_executable(char *find)
{
	char *tmp;

	if (ft_strncmp(find, "./", ft_strlen("./")) == 0)
		tmp = &find[2];
	else if (ft_strncmp(find, "/", ft_strlen("/")) == 0)
		tmp = find;
	else
		return (NULL);
	if (access(tmp, F_OK) == -1)
		return (NULL);
	if (access(tmp, X_OK) == -1)
	{
		ft_putstr_fd(find, 2);
		ft_putstr_fd(": Permission denied.\n", 2);
		exit(0);
	}
	return (find);
}

char	*find_cmd(char *find, char ***env)
{
	char	*var_path;
	char	**tab_path;
	char	*cmd;

	if ((cmd = is_executable(find)))
		return (cmd);
	if (!(*env))
		return (NULL);
	if (!(var_path = find_var_path((*env))))
		return (NULL);
	if (!(tab_path = ft_strsplit(&var_path[5], ':')))
		return (NULL);
	if ((create_absolute_path(find, &tab_path)) == -1)
		return (NULL);
	cmd = is_access_path(tab_path);
	ft_freetab(tab_path, ft_tablen(tab_path));
	return (cmd);
}
