/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:10:47 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/29 17:34:04 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mnsh.h"

int		d_redirection(const char *name)
{
	int		fd;

	fd = open(name, O_CREAT | O_WRONLY | O_APPEND,
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		write(2, "open error\n", 11);
	if (dup2(fd, 1) == -1)
		return (-1);
	return (1);
}

int		d_redirection_exe(char **param, t_term *term, int i)
{
	if (d_redirection(param[i + 2]) == -1)
		return (-1);
	param[i] = NULL;
	param[i + 1] = NULL;
	exec_cmd(&param[find_last_cmd(param, i - 1)], term);
	return (3);
}

int		d_is_redirection(char **param)
{
	if (param && param[0] != NULL && param[1] != NULL)
		if (ft_strcmp(param[0], ">>") == 0)
			return (1);
	return (-1);
}
