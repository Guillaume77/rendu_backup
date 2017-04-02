/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:10:01 by gubourge          #+#    #+#             */
/*   Updated: 2017/04/02 18:12:53 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "minishell.h"

void		pipe_loop(char **param, t_term *term, int i)
{
	free(param[i]);
	param[i] = NULL;
	pipe(term->pipefd);
	exec_cmd(&param[find_last_cmd(param, i - 1)], term, &(term->env));
}

int			pipe_exe(char **param, t_term *term, int i)
{
	term->flag = 1;
	pipe_loop(param, term, i);
	return (0);
}

int			is_pipe(char **param)
{
	if (param[0] != NULL && param[1] != NULL)
    {
		if (param[0][0] == '|' && param[0][1] == 0)
			return (1);
    }
	return (-1);
}
