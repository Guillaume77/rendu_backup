/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_transfert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:22:22 by gubourge          #+#    #+#             */
/*   Updated: 2016/12/15 14:41:30 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/param.h>
#include <unistd.h>
#include "minishell.h"

int		cd_new_oldpwd(char *new_oldpwd, char ***env)
{
	char	*tmp;
	char	**oldpwd;

	if (!(oldpwd = find_my(env, "OLDPWD")))
		return (-1);
	if (!(tmp = (char *)malloc(sizeof(char) *
		(ft_strlen("OLDPWD") + 1 + ft_strlen(new_oldpwd) + 1))))
		return (-1);
	ft_strcpy(tmp, "OLDPWD");
	ft_strcat(tmp, "=");
	ft_strcat(tmp, new_oldpwd);
	free(*oldpwd);
	*oldpwd = tmp;
	return (1);
}

int		cd_new_pwd(char *new_pwd, char ***env)
{
	char	*tmp;
	char	**pwd;

	if (!(pwd = find_my(env, "PWD")))
		return (-1);
	if (!(tmp = (char *)malloc(sizeof(char) *
		(ft_strlen("PWD") + 1 + ft_strlen(new_pwd) + 1))))
		return (-1);
	ft_strcpy(tmp, "PWD");
	ft_strcat(tmp, "=");
	ft_strcat(tmp, new_pwd);
	if ((cd_new_oldpwd(&(*pwd)[ft_strlen("PWD") + 1], env)) == -1)
		return (-1);
	free(*pwd);
	*pwd = tmp;
	return (1);
}

int		cd_go_to(char *new_path, char ***env)
{
	char	path[MAXPATHLEN];

	if (chdir(new_path) == -1)
		return (cd_error(new_path));
	if (!getcwd(path, MAXPATHLEN))
		return (-1);
	return (cd_new_pwd(path, env));
}
