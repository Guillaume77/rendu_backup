/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 12:06:34 by gubourge          #+#    #+#             */
/*   Updated: 2016/10/19 15:47:38 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "ft_ls.h"

int		initdir(DIR **dp, char **str, const char *path)
{
	*dp = opendir(path);
	if (*dp == NULL)
	{
		perror(path);
		return (-1);
	}
	if (!(*str = (char *)malloc(sizeof(char) * (ft_strlen(path) + NAME_MAX))))
		return (-1);
	return (1);
}

t_list	*listdir(const char *path)
{
	struct dirent	*entry;
	t_list			*list;
	DIR				*dp;
	char			*str;

	list = NULL;
	if ((initdir(&dp, &str, path)) == -1)
		return (NULL);
	while ((entry = readdir(dp)) != NULL)
	{
		str[0] = 0;
		ft_strcpy(str, path);
		if (path[ft_strlen(path) - 1] != '/')
			ft_strcat(str, "/");
		ft_strcat(str, entry->d_name);
		ft_list_push_back(&list, entry, str);
	}
	free(str);
	closedir(dp);
	return (list);
}

void	ft_ls(char *av, char op, int no_path, func_ptr *func_strcmp)
{
	t_list	*list;
	t_list	*tmp;

	if (av)
	{
		if (no_path)
			ft_ls_print(av);
		if (!(list = listdir(av)))
			return ;
		ft_list_sort(&list, op, func_strcmp);
		print_list(&list, op);
		tmp = list;
		if (list == NULL)
			return ;
		while (tmp)
		{
			if ((op & S_R) && S_ISDIR(tmp->stats.st_mode)
				&& (ft_strcmp(tmp->name, ".") && ft_strcmp(tmp->name, "..")))
				ft_ls(tmp->path, op, 1, func_strcmp);
			tmp = tmp->next;
		}
		ft_free_list(&list);
	}
}

void	ft_init_ls(int argc, char **argv, char op, func_ptr *func_strcmp)
{
	int	i;
	int	count;

	i = ft_advanced_sort_wordtab(&argv[1], &ft_strcmp);
	count = no_path(&argv[1]);
	while (++i < argc)
	{
		if (count > 1)
		{
			if (i > argc - count && i < argc)
				write(1, "\n", 1);
			write(1, argv[i], ft_strlen(argv[i]));
			write(1, ":\n", 2);
		}
		ft_ls(argv[i], op, 0, func_strcmp);
	}
}

int		main(int argc, char **argv)
{
	func_ptr	func_strcmp[255];
	char		op;

	op = 0;
	init_func_ptr(func_strcmp);
	if (argc > 1)
		if (ft_take_op(&argv[1], &op) == -1)
		{
			write(2, argv[0], ft_strlen(argv[0]));
			write(2, ": illegal option -- ", ft_strlen(": illegal option -- "));
			write(2, &op, 1);
			write(2, "\nusage: ", ft_strlen("\nusage: "));
			write(2, argv[0], ft_strlen(argv[0]));
			write(2, " [-alRrt] [file ...]\n",
					ft_strlen(" [-alRrt] [file ...]\n"));
			return (1);
		}
	if (!no_path(&argv[1]))
		ft_ls(".", op, 0, func_strcmp);
	else
		ft_init_ls(argc, argv, op, func_strcmp);
	return (0);
}
