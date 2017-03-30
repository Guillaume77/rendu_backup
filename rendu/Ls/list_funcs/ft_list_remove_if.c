/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 18:19:18 by gubourge          #+#    #+#             */
/*   Updated: 2016/09/21 14:55:36 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include "ft_ls.h"

void		ft_list_remove_if(t_list **begin_list)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *begin_list;
	prev = NULL;
	while (tmp)
	{
		if (!S_ISDIR((*begin_list)->stats.st_mode))
		{
			*begin_list = (*begin_list)->next;
			ft_free_all(tmp);
			tmp = *begin_list;
		}
		else if (!S_ISDIR(tmp->stats.st_mode))
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
