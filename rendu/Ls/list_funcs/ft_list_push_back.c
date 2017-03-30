/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 18:51:17 by gubourge          #+#    #+#             */
/*   Updated: 2016/10/19 15:58:39 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include "ft_ls.h"

void	ft_list_push_back(t_list **begin_list, struct dirent *entry,
						const char *path)
{
	t_list	*tmp;

	tmp = *begin_list;
	if (tmp == NULL)
	{
		*begin_list = ft_create_elem(entry, path);
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_create_elem(entry, path);
}
