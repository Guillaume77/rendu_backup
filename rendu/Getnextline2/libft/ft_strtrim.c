/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 14:23:13 by gubourge          #+#    #+#             */
/*   Updated: 2016/05/12 13:52:00 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		++i;
	while ((s[j] == ' ' || s[j] == '\n' || s[j] == '\t') && s[i])
		--j;
	if ((str = (char *)malloc(sizeof(char) * (j - i + 2))) == NULL)
		return (NULL);
	k = 0;
	while (i <= j && s[i])
	{
		str[k] = s[i];
		++k;
		++i;
	}
	str[k] = 0;
	return (str);
}
