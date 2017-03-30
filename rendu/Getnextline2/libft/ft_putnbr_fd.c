/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:18:22 by gubourge          #+#    #+#             */
/*   Updated: 2016/03/10 15:26:39 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	count;
	long int	nb_tempo;

	nb_tempo = n;
	count = 1;
	if (nb_tempo == 0)
		return (ft_putchar_fd('0', fd));
	if (nb_tempo < 0)
	{
		ft_putchar_fd('-', fd);
		nb_tempo *= -1;
	}
	while (count <= nb_tempo)
		count *= 10;
	while (count > 1)
	{
		count /= 10;
		ft_putchar_fd((nb_tempo / count % 10 + 48), fd);
	}
}
