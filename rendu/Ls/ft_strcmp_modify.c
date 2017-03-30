/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_modify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 16:42:22 by gubourge          #+#    #+#             */
/*   Updated: 2016/10/18 16:58:22 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_strcmp_modify(const t_list *s1, const t_list *s2)
{
	int	i;

	i = 0;
	while (s1->name[i] == s2->name[i] && s1->name[i] && s2->name[i])
		++i;
	if (((unsigned char*)s1->name)[i] > ((unsigned char*)s2->name)[i])
		return (((unsigned char*)s1->name)[i] - ((unsigned char*)s2->name)[i]);
	else if (((unsigned char*)s1->name)[i] < ((unsigned char*)s2->name)[i])
		return (((unsigned char*)s1->name)[i] - ((unsigned char*)s2->name)[i]);
	return (0);
}
