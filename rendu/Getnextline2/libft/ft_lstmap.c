/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 16:12:38 by gubourge          #+#    #+#             */
/*   Updated: 2016/05/12 13:34:10 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	if (!(new = f(lst)))
		return (NULL);
	tmp = new;
	while (lst->next)
	{
		lst = lst->next;
		if (!(tmp->next = f(lst)))
			return (NULL);
		tmp = tmp->next;
	}
	return (new);
}
