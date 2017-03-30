/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/22 13:34:02 by gubourge          #+#    #+#             */
/*   Updated: 2016/03/10 18:11:57 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int	ft_recur_str(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (s1[i] == s2[i] && s2[i])
		++i;
	if (s2[i] == 0)
		return (1);
	return (-1);
}

char		*ft_strstr(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	if (!s2[0])
		return ((char *)s1);
	while (s1[i])
	{
		if (ft_recur_str(&s1[i], s2) == 1)
			return (&((char *)s1)[i]);
		++i;
	}
	return (NULL);
}
