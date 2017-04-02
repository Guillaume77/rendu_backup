/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_redirection_gauche.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:10:57 by gubourge          #+#    #+#             */
/*   Updated: 2017/04/02 18:12:42 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"

int		change_prompt(t_term *term, int flag)
{
	if (term->prompt)
		free(term->prompt);
	if (flag == 1)
	{
		if (!(term->prompt = ft_strdup(PROMPT_HEREDOC)))
			return (-1);
	}
	else if (flag == 0)
	{
		if (!(term->prompt = ft_strdup(PROMPT)))
			return (-1);
	}
	return (0);
}

int		d_l_redirection(char *name, t_term *term)
{
	char		*line;

	if (change_prompt(term, 1) == -1)
		return (-1);
	ft_putstr(term->prompt);
	if (set_termcaps(term, 0) == -1)
		return (-1);
	while ((ft_termcaps(&line, term)) > 0)
    {
		if (ft_strcmp(line, name) != 0)
		{
			ft_putstr_fd(line, (term->pipefd)[1]);
			ft_putchar_fd('\n', (term->pipefd)[1]);
		}
		else
		{
			if ((change_prompt(term, 0)) == -1)
				return (-1);
			if ((set_termcaps(term, 1)) == -1)
				return (-1);
			if ((close(term->pipefd[1])) == -1 || (dup2((term->pipefd)[0], 0)) == -1)
				return (-1);
			return (1);
		}
		ft_putstr(term->prompt);
		free(line);
    }
	if ((change_prompt(term, 0)) == -1)
		return (-1);
	if ((set_termcaps(term, 0)) == -1)
		return (-1);
	if ((close(term->pipefd[1])) == -1 || (dup2((term->pipefd)[0], 0)) == -1)
		return (-1);
	return (1);
}

int		d_l_redirection_exe(char **param, t_term *term, int i)
{
	if (param[i + 1] == NULL)
    {
		write(2, D_R_G_ERROR_MSG, ft_strlen(D_R_G_ERROR_MSG));
		return (-1);
    }
	free(param[i]);
	param[i] = NULL;
	if (pipe(term->pipefd) == -1)
		return (-1);
	if (d_l_redirection(param[i + 1], term) == -1)
	{
		free(param[i + 1]);
		param[i + 1] = NULL;
		return (-1);
	}
	exec_cmd(&param[find_last_cmd(param, i - 1)], term, &(term->env));
	close((term->pipefd)[0]);
	dup2(term->sv_0, 0);
	free(param[i + 1]);
	param[i + 1] = NULL;
	return (2);
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
