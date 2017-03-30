/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 18:07:58 by gubourge          #+#    #+#             */
/*   Updated: 2016/10/19 15:18:25 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_putchar(char c)
{
	write(1, &c, 1);
}

void			ft_putnbr(long long int n)
{
	long long int	count;
	long long int	nb_tempo;

	nb_tempo = n;
	count = 1;
	if (nb_tempo == 0)
		return (ft_putchar('0'));
	if (nb_tempo < 0)
	{
		ft_putchar('-');
		nb_tempo *= -1;
	}
	while (count <= nb_tempo)
		count *= 10;
	while (count > 1)
	{
		count /= 10;
		ft_putchar((nb_tempo / count % 10 + 48));
	}
}
