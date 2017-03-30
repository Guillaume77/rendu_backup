/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 14:50:54 by gubourge          #+#    #+#             */
/*   Updated: 2017/01/19 14:59:30 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include "minishell.h"

int		ft_free_utils(char **line, char ***param, int ret)
{
	if (*line)
		free(*line);
	ft_freetab(*param, ft_tablen(*param));
	return (ret);
}

int		exec_cmd(char **param, char ***env)
{
	pid_t	father;
	char	*cmd;

	if ((father = fork()) == -1)
	{
		ft_putstr_fd("Error: in ft_minishell.c: fork didn't work\n", 2);
		return (-1);
	}
	if (father == 0)
	{
		cmd = find_cmd(param[0], env);
		execve(cmd, param, *env);
		ft_putstr_fd(param[0], 2);
		ft_putstr_fd(": Command not found.\n", 2);
		exit(-1);
	}
	waitpid(father, NULL, 0);
/*	if (signal(SIGINT, quit_handler) == SIG_ERR)
		return (-1);
*/	return (0);
}

int		ft_minishell(t_builtin *builtin, char ***env)
{
	char	**param;
	char	*line;
	int		ret;

	while (ft_get_line(0, &line) > 0)
	{
		if ((param = ft_split_whitespaces(line)))
			if (param[0])
			{
				ret = is_built_in(builtin, param, env);
				if (ft_strcmp(param[0], "exit") != 0 && ret == -2)
				{
					if (exec_cmd(param, env) == -1)
						return (ft_free_utils(&line, &param, -1));
				}
				else if (ft_strcmp(param[0], "exit") == 0 && ret != -2)
					return (ft_free_utils(&line, &param, ret));
			}
		ft_free_utils(&line, &param, 0);
		ft_putstr_fd("$>", 1);
	}
	return (0);
}
