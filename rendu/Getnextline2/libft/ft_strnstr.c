/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 16:45:33 by gubourge          #+#    #+#             */
/*   Updated: 2016/03/10 18:22:12 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

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

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!s2[0])
		return ((char *)s1);
	len = ft_strlen((char *)s2);
	while (s1[i] && n >= len)
	{
		if (ft_recur_str(&s1[i], s2) == 1)
			return (&((char *)s1)[i]);
		++i;
		--n;
	}
	return (NULL);
}
