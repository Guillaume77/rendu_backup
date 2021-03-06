/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_rt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 13:59:19 by gubourge          #+#    #+#             */
/*   Updated: 2016/10/18 16:53:58 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "ft_ls.h"

int		ft_strcmp_rt(const t_list *s1, const t_list *s2)
{
	if (s1->stats.st_mtime > s2->stats.st_mtime)
		return (1);
	else if (s1->stats.st_mtime < s2->stats.st_mtime)
		return (0);
	else
	{
		if (s1->stats.st_mtimespec.tv_sec > s2->stats.st_mtimespec.tv_sec)
			return (1);
		else if (s1->stats.st_mtimespec.tv_sec < s2->stats.st_mtimespec.tv_sec)
			return (0);
		else
		{
			if (s1->stats.st_mtimespec.tv_nsec > s2->stats.st_mtimespec.tv_nsec)
				return (1);
			else if (s1->stats.st_mtimespec.tv_nsec <
					s2->stats.st_mtimespec.tv_nsec)
				return (0);
		}
	}
	return (ft_strcmp_r(s1, s2));
}
