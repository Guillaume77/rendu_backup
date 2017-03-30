/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 14:45:18 by gubourge          #+#    #+#             */
/*   Updated: 2016/10/18 16:59:29 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_strcmp_r(const t_list *s1, const t_list *s2)
{
	int	i;

	i = 0;
	while (s1->name[i] == s2->name[i] && s1->name[i] && s2->name[i])
		++i;
	if (((unsigned char*)s1->name)[i] < ((unsigned char*)s2->name)[i])
		return (((unsigned char*)s2->name)[i] - ((unsigned char*)s1->name)[i]);
	else if (((unsigned char*)s1->name)[i] < ((unsigned char*)s2->name)[i])
		return (((unsigned char*)s2->name)[i] - ((unsigned char*)s1->name)[i]);
	return (0);
}
