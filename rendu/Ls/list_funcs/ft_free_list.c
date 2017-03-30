/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 12:09:13 by gubourge          #+#    #+#             */
/*   Updated: 2016/09/21 15:02:12 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

void		ft_free_all(t_list *list)
{
	free(list->name);
	free(list->path);
	free(list);
	list = NULL;
}

void		ft_free_list(t_list **begin_list)
{
	t_list	*tmp;

	tmp = *begin_list;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		*begin_list = (*begin_list)->next;
		ft_free_all(tmp);
		tmp = *begin_list;
	}
}
