/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 15:57:29 by gubourge          #+#    #+#             */
/*   Updated: 2016/04/25 16:27:58 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*next;

	tmp = *alst;
	next = tmp->next;
	while (tmp)
	{
		ft_lstdelone(&tmp, del);
		tmp = next;
		if (next)
			next = next->next;
	}
	*alst = NULL;
}
