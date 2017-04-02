/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:42:14 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/29 18:28:41 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int			cd_error(char *param)
{
	write(2, param, ft_strlen(param));
	write(2, ": No such file or directory.\n",
			ft_strlen(": No such file or directory.\n"));
	return (-1);
}

static int	cd_go_home(char ***env)
{
	char	**tmp;

	if (!(tmp = find_my(env, "HOME")))
		return (-1);
	if (chdir(&(*tmp)[ft_strlen("HOME") + 1]) == -1)
		return (cd_error(&(*tmp)[ft_strlen("HOME") + 1]));
	return (cd_new_pwd(&(*tmp)[ft_strlen("HOME") + 1], env));
}

static int	cd_back(char ***env)
{
	char	**tmp;

	if (!(tmp = find_my(env, "OLDPWD")))
		return (-1);
	if (chdir(&(*tmp)[ft_strlen("OLDPWD") + 1]))
	{
		write(2, "OLDPWD not set\n", 15);
		return (-1);
	}
	return (cd_new_pwd(&(*tmp)[ft_strlen("OLDPWD") + 1], env));
}

int			ft_cd(char **param, char ***env)
{
	if (*env && !param[1])
		return (cd_go_home(env));
	else if (*env && ft_strcmp(param[1], "-") == 0)
		return (cd_back(env));
	if (!param[2])
		return (cd_go_to(param[1], env));
	else
		ft_putstr_fd("cd: Too many arguments.\n", 2);
	return (1);
}
