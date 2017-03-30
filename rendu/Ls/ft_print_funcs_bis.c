/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_funcs_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 14:57:29 by gubourge          #+#    #+#             */
/*   Updated: 2016/10/19 15:20:22 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls_print(char *av)
{
	write(1, "\n", 1);
	write(1, av, ft_strlen(av));
	write(1, ":\n", 2);
}

void	print_list(t_list **list, char op)
{
	t_list	*tmp;

	if (op & S_l)
		print_list_l(list);
	else
	{
		tmp = *list;
		while (tmp)
		{
			write(1, tmp->name, ft_strlen(tmp->name));
			write(1, "\n", 1);
			tmp = tmp->next;
		}
	}
}
