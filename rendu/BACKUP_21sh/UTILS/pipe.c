/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:10:01 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/29 17:36:48 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "mnsh.h"

void		pipe_loop(char **param, t_term *term, int i)
{
	int		pipefd[2];

	pipe(pipefd);
	param[i] = NULL;
	dup2(pipefd[1], 1);
// flag == 0
	exec_cmd(&param[find_last_cmd(param, i - 1)], term);
	close(pipefd[1]);
	dup2(pipefd[0], 0);
}

int			pipe_exe(char **param, t_term *term, int i)
{
	pipe_loop(param, term, i);
	return (1);
}

int			is_pipe(char **param)
{
	if (param[0] != NULL && param[1] != NULL)
    {
		if (ft_strcmp(param[0][0], "|") == 0 &&
			ft_strcmp(param[0][1], "|") != 0)
			return (1);
    }
	return (-1);
}
