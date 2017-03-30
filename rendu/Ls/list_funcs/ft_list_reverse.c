/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 17:55:14 by gubourge          #+#    #+#             */
/*   Updated: 2016/04/14 16:26:12 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

void		ft_list_reverse(t_list **begin_list)
{
	t_list	*tmp;
	t_list	*first;

	tmp = *begin_list;
	first = *begin_list;
	if (tmp && tmp->next)
	{
		first = tmp->next;
		ft_list_reverse(&(tmp->next));
		first->next = tmp;
		*begin_list = tmp->next;
		first->next->next = NULL;
	}
}
