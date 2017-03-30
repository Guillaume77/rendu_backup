/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 14:37:48 by gubourge          #+#    #+#             */
/*   Updated: 2016/05/12 13:52:13 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	nb_split(char const *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			++nb;
			while (s[i] != c && s[i])
				++i;
		}
		while (s[i] == c && s[i])
			++i;
	}
	return (nb);
}

static char	*split_strdup(char const *s, int *i, char c)
{
	char	*str;
	int		save;
	int		j;

	save = *i;
	while (s[*i] != c && s[*i])
		++(*i);
	if ((str = (char *)malloc(sizeof(char) *
		(*i - save + 1))) == NULL)
		return (NULL);
	j = 0;
	while (s[save] != c && s[save])
	{
		str[j] = s[save];
		++j;
		++save;
	}
	str[j] = 0;
	return (str);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	if ((tab = (char **)malloc(sizeof(char *) *
		(nb_split(s, c) + 1))) == NULL)
		return (NULL);
	i = 0;
	j = -1;
	while (s[i])
	{
		if (s[i] != c)
			if ((tab[++j] = split_strdup(s, &i, c)) == NULL)
				return (NULL);
		while (s[i] == c && s[i])
			++i;
	}
	tab[++j] = NULL;
	return (tab);
}
