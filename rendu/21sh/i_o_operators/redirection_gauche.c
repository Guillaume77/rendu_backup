/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_gauche.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:02:42 by gubourge          #+#    #+#             */
/*   Updated: 2017/04/02 18:13:53 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"

int		l_redirection(const char *name)
{
	int		fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		ft_putstr_fd(OPEN_ERROR_MSG, 2);
	if (dup2(fd, 0) == -1)
		return (-1);
	return (fd);
}

int		l_redirection_exe(char **param, t_term *term, int i)
{
	int		fd;

	free(param[i]);
	param[i] = NULL;
	if ((fd = l_redirection(param[i + 1])) == -1)
	{
		dup2(term->sv_0, 0);
		close(fd);
		free(param[i + 1]);
		param[i + 1] = NULL;
		return (0);
	}
	exec_cmd(&param[find_last_cmd(param, i - 1)], term, &(term->env));
	dup2(term->sv_0, 0);
	close(fd);
	free(param[i + 1]);
	param[i + 1] = NULL;
	return (2);
}

int		l_is_redirection(char **param)
{
	if (param && param[0] != NULL && param[1] != NULL)
		if (ft_strcmp(param[0], "<") == 0)
			return (1);
	return (-1);
}
