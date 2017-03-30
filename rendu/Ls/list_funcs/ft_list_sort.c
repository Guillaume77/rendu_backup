/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 17:33:38 by gubourge          #+#    #+#             */
/*   Updated: 2016/10/19 16:08:28 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <errno.h>
#include "ft_ls.h"

static void		ft_swap(t_list *l1, t_list *l2, int *count)
{
	char			*c;
	struct stat		d;

	*count = 1;
	d = l1->stats;
	l1->stats = l2->stats;
	l2->stats = d;
	c = l1->name;
	l1->name = l2->name;
	l2->name = c;
	c = l1->usr_name;
	l1->usr_name = l2->usr_name;
	l2->usr_name = c;
	c = l1->grp_name;
	l1->grp_name = l2->grp_name;
	l2->grp_name = c;
	c = l1->path;
	l1->path = l2->path;
	l2->path = c;
}

void			ft_list_sort(t_list **begin_list, char op,
					func_ptr *func_strcmp)
{
	t_list	*tmp;
	t_list	*prev;
	int		count;

	if (!(op & S_a))
		ft_n_a(begin_list);
	else
		op -= 1;
	if (!(*begin_list))
		return ;
	count = 1;
	while (count)
	{
		count = 0;
		tmp = (*begin_list)->next;
		prev = *begin_list;
		while (tmp)
		{
			if (func_strcmp[(int)op](prev, tmp) > 0)
				ft_swap(prev, tmp, &count);
			tmp = tmp->next;
			prev = prev->next;
		}
	}
}
