/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 14:50:54 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/29 19:04:52 by gubourge         ###   ########.fr       */
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

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s - %d\n", tab[i], i);
		++i;
	}
}

char	**get_param(char *line)
{
	char	**split_wsp;
	char	**param;

	if (!(split_wsp = ft_split_whitespaces(line)))
		return (NULL);
	if (!(param = ft_parse(split_wsp)))
		return (NULL);
	ft_freetab(split_wsp, ft_tablen(split_wsp));
	return (param);
}

int		ft_minishell(t_builtin *builtin, t_term *term)
{
	char	**param;
	char	*line;
	int		ret;

	while ((ret = ft_termcaps(&line, term)) > 0)
	{
		if (ret == 2)
			return (0);
		if ((param = ft_split_whitespaces(line)))
			if (param[0])
			{
				if (ft_put_history(term, line) == -1)
					return (-1);
				ft_cp_history(term);
				if ((ret = command_exe(param, term, builtin)) == -1)
					return (-1);
/*				ret = is_built_in(term->builtin, param, &(term->env));
				if (ft_strcmp(param[0], "exit") != 0 && ret == -2)
				{
					if (exec_cmd(param, term) == -1)
					return (ft_free_utils(&line, &param, -1));
					}
					else if (ft_strcmp(param[0], "exit") == 0 && ret != -2)
					return (ft_free_utils(&line, &param, ret));
*/			}
		ft_free_utils(&line, &param, 0);
		ft_putstr_fd(PROMPT, 1);
	}
	return (0);
}
