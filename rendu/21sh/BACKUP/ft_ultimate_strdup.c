/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_strdup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 15:23:53 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/29 16:08:26 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int		ft_ultimate_strlen(char **tab, int length)
{
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (i < length)
	{
		size += ft_strlen(tab[i]);
		++i;
	}
	return (size);
}

char	*ft_ultimate_strdup(char **tab, int length)
{
	char	*dest;
	int		i;
	int		size;
	int		count;

	if (length == 0)
		return (NULL);
	count = length - 1;
	size = ft_ultimate_strlen(tab, length);
	if ((dest = (char *)malloc(sizeof(char) * (size + count + 1))) == NULL)
		return (NULL);
	i = 0;
	*dest = 0;
	while (i < length)
	{
		ft_strcat(dest, tab[i]);
		++i;
		if (count > 0)
		{
			ft_strcat(dest, " ");
			count--;
		}
	}
	return (dest);
}
