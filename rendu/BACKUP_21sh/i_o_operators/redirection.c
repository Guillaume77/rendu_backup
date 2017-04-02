/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:01:44 by gubourge          #+#    #+#             */
/*   Updated: 2017/04/02 18:13:24 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"

int		redirection(const char *name)
{
	int		fd;

	fd = open(name, O_CREAT | O_TRUNC | O_WRONLY,
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		ft_putstr_fd(OPEN_ERROR_MSG, 2);
	if (dup2(fd, 1) == -1)
		return (-1);
	return (fd);
}

void			quit_handler2(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		exit(1);
	}
}

void		read_output()
{
	char	buffer[BUFF_SIZE + 1];
	int		ret;
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
		while ((ret = read(0, buffer, BUFF_SIZE)) > 0)
		{
			buffer[ret] = 0;
			write(1, buffer, ft_strlen(buffer));
			signal(SIGINT, quit_handler2);
		}
		exit(1);
	}
	waitpid(pid, NULL, 0);
}

int		redirection_exe(char **param, t_term *term, int i)
{
	int	fd;

	free(param[i]);
	param[i] = NULL;
	if ((fd = redirection(param[i + 1])) == -1)
	{
		dup2(term->sv_1, 1);
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

int		is_redirection(char **param)
{
	if (param && param[0] != NULL && param[1] != NULL)
		if (ft_strcmp(param[0], ">") == 0)
			return (1);
		if (ft_strcmp(param[0], "2>") == 0)
			return (1);
		if (ft_strcmp(param[0], "1>") == 0)
			return (1);
		if (ft_strcmp(param[0], "2>&-") == 0)
			return (1);
		if (ft_strcmp(param[0], "2>&1") == 0)
			return (1);
		if (ft_strcmp(param[0], "1>&-") == 0)
			return (1);
	return (-1);
}
