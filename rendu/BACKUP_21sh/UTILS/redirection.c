/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:01:44 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/29 17:31:09 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mnsh.h"

int		find_last_cmd(char **param, int i)
{
	if (i < 0)
		return (0);
	while (param[i] && i > 0)
		--i;
	if (param[i] == NULL && param[i + 1])
		return (i + 1);
	else
		return (i);
}

int		redirection(const char *name)
{
	int		fd;

	fd = open(name, O_CREAT | O_TRUNC | O_WRONLY,
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		ft_putstr_fd(OPEN_ERROR_MSG, 2);
	if (dup2(fd, 1) == -1)
		return (-1);
	return (1);
}

int		redirection_exe(char **param, t_term *term, int i)
{
	char	*str

	if (redirection(param[i + 1]) == -1)
		return (0);
	param[i] = NULL;
	// si param[i - 1] NULL read sur 0
	exec_cmd(&param[find_last_cmd(param, i - 1)], term);
	return (1);
}

int		is_redirection(char **param)
{
	if (param[0] != NULL && param[1] != NULL)
		if (ft_strcmp(param[0], ">") == 0)
			return (1);
	return (-1);
}
