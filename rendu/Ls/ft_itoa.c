/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 15:26:15 by gubourge          #+#    #+#             */
/*   Updated: 2016/08/10 17:55:05 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void		init_itoa(int *cpt, long int *count, long int *nb, int nbr)
{
	*cpt = 1;
	*nb = nbr;
	if (*nb < 0)
	{
		(*nb) *= -1;
		(*cpt)++;
	}
	*count = 1;
}

static void		count_nb(long int nb, long int *count, int *cpt)
{
	while (nb > 9)
	{
		(*count) *= 10;
		nb /= 10;
		(*cpt)++;
	}
}

char			*ft_itoa(int n)
{
	long int	nb;
	int			i;
	long int	count;
	char		*str;
	int			cpt;

	init_itoa(&cpt, &count, &nb, n);
	count_nb(nb, &count, &cpt);
	if ((str = (char *)malloc(sizeof(char) * (cpt + 1))) == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str[i++] = '-';
		cpt--;
	}
	while (cpt--)
	{
		str[i++] = ((nb / count % 10) + 48);
		count /= 10;
	}
	str[i] = 0;
	return (str);
}
