/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_n_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 19:15:15 by gubourge          #+#    #+#             */
/*   Updated: 2016/09/21 14:44:28 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

void	ft_n_a(t_list **list)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *list;
	prev = NULL;
	while (tmp)
	{
		if ((*list)->name[0] == '.')
		{
			*list = (*list)->next;
			ft_free_all(tmp);
			tmp = *list;
		}
		else if (tmp->name[0] == '.')
		{
			prev->next = tmp->next;
			ft_free_all(tmp);
			tmp = prev->next;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
