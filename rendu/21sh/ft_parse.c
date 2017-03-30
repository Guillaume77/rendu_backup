/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 13:13:17 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/29 16:07:40 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int			ft_cmd_is_sep(char *str)
{
	int		i;

	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 ||
		ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0 ||
		ft_strcmp(str, "|") == 0) 
		return (1);
	i = -1;
	while (str[++i])
		if (str[i] == '>' || str[i] == '<')
			return (1);
	return (0);
}

int			ft_nb_cmd(char **tab)
{
	int		i;
	int		cmd;
	int		rep;

	i = 0;
	cmd = 0;
	rep = 0;
	while (tab[i])
	{
		if (ft_cmd_is_sep(tab[i]) == 1)
		{
			cmd++;
			rep = 0;
		}
		else if (!rep)
		{
			cmd++;
			rep = 1;
		}
		i++;
	}
	return (cmd);
}

char		*ft_find_cmd(char **tab, int *i)
{
	int		j;

	if (ft_cmd_is_sep(tab[*i]) == 1)
	{
		++(*i);
		return (ft_ultimate_strdup(&tab[*i - 1], 1));
	}
	else
	{
		j = 0;
		while (tab[*i] && ft_cmd_is_sep(tab[*i]) == 0)
		{
			++j;
			++(*i);
		}
	}
	if (j == 0)
		return (NULL);
	return (ft_ultimate_strdup(&tab[*i - j], j));
}

char		**ft_parse(char **tab)
{
	char	**parse;
	int		nb_cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nb_cmd = ft_nb_cmd(tab);
	if ((parse = (char **)malloc(sizeof(char *) * (nb_cmd + 1))) == NULL)
		return (NULL);
	while (j < nb_cmd)
	{
		if ((parse[j] = ft_find_cmd(tab, &i)) == NULL)
			return (NULL);
		++j;
	}
	parse[j] = NULL;
	return (parse);
}
