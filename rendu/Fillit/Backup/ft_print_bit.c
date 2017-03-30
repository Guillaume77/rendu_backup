/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:05:58 by gubourge          #+#    #+#             */
/*   Updated: 2016/03/23 15:38:07 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fillit.h"

void	print_bit(int *tab, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = 0;
		while (j < size)
		{
			putchar('0' + ((tab[i] >> j) & 1));
			++j;
		}
		putchar('\n');
	}
	putchar('\n');
}

void	print_square(t_tetri *tetris, int size)
{
	int		i;
	int		j;
	int		dec_bit;
	char	count;

	i = -1;
	while (++i < size)
	{
		dec_bit = -1;
		while (++dec_bit < size)
		{
			count = 1;
			j = -1;
			while (++j < tetris->nb_tetris)
				if ((TET[j].tetris[i] >> dec_bit) & 1)
				{
					count = 0;
//					print_bit(TET[j].tetris, 10);
//					putchar('\n');
					write(1, &(TET[j].carac), 1);
//					putchar('\n');
//					sleep(2);
				}
			if (count)
				write(1, ".", 1);
		}
		write(1, "\n", 1);
	}
}
