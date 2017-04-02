/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 14:50:54 by gubourge          #+#    #+#             */
/*   Updated: 2017/04/02 18:43:35 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include "minishell.h"

int		ft_free_utils(char *line, char **param, int length_tab, int ret)
{
	if (line)
		free(line);
	if (length_tab == 0)
		ft_freetab(param, ft_tablen(param));
	else
		ft_freetab(param, length_tab);
	return (ret);
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
	int		length_tab;

	while ((ret = ft_termcaps(&line, term)) > 0)
	{
		if (ret == 2)
			return (0);
		length_tab = 0;
		if ((param = ft_split_whitespaces(line)) && param[0])
		{
			length_tab = ft_tablen(param);
			if (ft_put_history(term, line) == -1)
				return (ft_free_utils(line, param, length_tab, -1));
			ft_cp_history(term);
			if ((ret = command_exe(param, term, builtin)) == -1)
				return (ft_free_utils(line, param, length_tab, ret));
			if (term->flag == 2)
				return (ft_free_utils(line, param, length_tab, ret));
		}
		ft_free_utils(line, param, length_tab, 0);
		ft_putstr_fd(PROMPT, 1);
	}
	return (0);
}
