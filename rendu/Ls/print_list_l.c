/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 15:59:27 by gubourge          #+#    #+#             */
/*   Updated: 2016/10/19 15:50:10 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "ft_ls.h"

void	init_padd(long unsigned int **padd)
{
	(*padd)[0] = 0;
	(*padd)[1] = 0;
	(*padd)[2] = 0;
	(*padd)[3] = 0;
}

void	print_node_l_bis(t_list *tmp, long unsigned int **padd)
{
	print_mode(tmp->stats.st_mode);
	print_perms(tmp->stats.st_mode);
	print_padd((*padd)[0], ft_strlen(ft_itoa(tmp->stats.st_nlink)));
	write(1, "  ", 2);
	ft_putnbr(tmp->stats.st_nlink);
	write(1, " ", 1);
	write(1, tmp->usr_name, ft_strlen(tmp->usr_name));
	print_padd((*padd)[1], ft_strlen(tmp->usr_name));
	write(1, "  ", 2);
	write(1, tmp->grp_name, ft_strlen(tmp->grp_name));
	write(1, " ", 1);
	print_padd((*padd)[2], ft_strlen(tmp->grp_name));
	print_padd((*padd)[3], ft_strlen(ft_itoa(tmp->stats.st_size)));
	write(1, " ", 2);
	ft_putnbr(tmp->stats.st_size);
}

void	print_node_l(t_list **list, long unsigned int **padd)
{
	t_list				*tmp;
	char				*cpy;

	tmp = *list;
	while (tmp)
	{
		print_node_l_bis(tmp, padd);
		if ((print_date(tmp->stats)) == -1)
			return ;
		write(1, " ", 1);
		write(1, tmp->name, ft_strlen(tmp->name));
		if (S_ISLNK(tmp->stats.st_mode))
		{
			cpy = (char *)malloc(sizeof(char) * tmp->stats.st_size + 1);
			readlink(tmp->path, cpy, tmp->stats.st_size + 1);
			cpy[tmp->stats.st_size] = 0;
			write(1, " -> ", 4);
			write(1, cpy, ft_strlen(cpy));
			free(cpy);
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	ft_list_remove_if(list);
	free(*padd);
}

void	print_list_l(t_list **list)
{
	t_list				*tmp;
	long long int		blocks;
	long unsigned int	*padd;

	blocks = 0;
	tmp = *list;
	padd = (long unsigned int *)malloc(sizeof(long unsigned int) * 4);
	init_padd(&padd);
	while (tmp)
	{
		blocks += tmp->stats.st_blocks;
		if (padd[0] < ft_strlen(ft_itoa(tmp->stats.st_nlink)))
			padd[0] = ft_strlen(ft_itoa(tmp->stats.st_nlink));
		if (padd[1] < ft_strlen(tmp->usr_name))
			padd[1] = ft_strlen(tmp->usr_name);
		if (padd[2] < ft_strlen(tmp->grp_name))
			padd[2] = ft_strlen(tmp->grp_name);
		if (padd[3] < ft_strlen(ft_itoa(tmp->stats.st_size)))
			padd[3] = ft_strlen(ft_itoa(tmp->stats.st_size));
		tmp = tmp->next;
	}
	write(1, "total ", ft_strlen("total "));
	ft_putnbr(blocks);
	write(1, "\n", 1);
	print_node_l(list, &padd);
}
