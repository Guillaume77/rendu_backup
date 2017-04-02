/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:10:47 by gubourge          #+#    #+#             */
/*   Updated: 2017/04/02 18:12:01 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"

int		d_redirection(const char *name)
{
	int		fd;

	fd = open(name, O_CREAT | O_WRONLY | O_APPEND,
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		ft_putstr_fd(OPEN_ERROR_MSG, 2);
	if (dup2(fd, 1) == -1)
		return (-1);
	return (fd);
}

int		d_redirection_exe(char **param, t_term *term, int i)
{
	int	fd;

	free(param[i]);
	param[i] = NULL;
	if ((fd = d_redirection(param[i + 1])) == -1)
	{
		dup2(term->sv_0, 0);
		close(fd);
		free(param[i + 1]);
		param[i + 1] = NULL;
		return (0);
	}
	if (i == 0 || !param[i - 1])
		read_output();
	else
		exec_cmd(&param[find_last_cmd(param, i - 1)], term, &(term->env));
	dup2(term->sv_1, 1);
	close(fd);
	free(param[i + 1]);
	param[i + 1] = NULL;
	return (2);
}

int		d_is_redirection(char **param)
{
	if (param && param[0] != NULL && param[1] != NULL)
		if (ft_strcmp(param[0], ">>") == 0)
			return (1);
	return (-1);
}
