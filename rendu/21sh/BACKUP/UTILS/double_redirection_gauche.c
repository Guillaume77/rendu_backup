/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_redirection_gauche.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:10:57 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/29 17:35:33 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mnsh.h"

int		d_l_redirection(char *name)
{
	char		*s;
	int		pipefd2[2];

	if ((pipe(pipefd2)) == -1)
		return (-1);
	write(2, ">", 1);
/*	while ((s = get_next_line(0)) != NULL)
    {
		if (ft_strcmp(s, name) != 0)
		{
			write(pipefd2[1], s, ft_strlen(s));
			write(pipefd2[1], "\n", 1);
		}
		else
		{
			if ((close(pipefd2[1])) == -1 || (dup2(pipefd2[0], 0)) == -1)
				return (-1);
			return (1);
		}
		write(2, ">", 1);
		free(s);
    }
	if ((close(pipefd2[1])) == -1 || (dup2(pipefd2[0], 0)) == -1)
		return (-1);
	return (1);
*/
}

int		d_l_redirection_exe(char **param, t_term *term, int i)
{
	if (param[i + 1] == NULL)
    {
		write(2, D_R_G_ERROR_MSG, ft_strlen(D_R_G_ERROR_MSG));
		return (-1);
    }
	if (dg_redirection(param[i + 1]) == -1)
		return (-1);
	param[i] = NULL;
	param[i + 1] = NULL;
	exec_cmd(&param[find_last_cmd(param, i - 1)], term);
	return (3);
}

int		d_l_is_redirection(char **param)
{
	if (param && param[0] != NULL && param[1] != NULL)
    {
		if (ft_strcmp(param[0], "<<") == 0)
			return (1);
    }
	return (-1);
}
