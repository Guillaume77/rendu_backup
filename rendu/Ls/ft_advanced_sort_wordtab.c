/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_advanced_sort_wordtab.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 17:30:24 by gubourge          #+#    #+#             */
/*   Updated: 2016/09/14 15:25:56 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

static int	escape_option(char **tab)
{
	int	i;

	i = 0;
	while (tab[i][0] == '-' && tab[i][1] != 0)
		++i;
	return (i);
}

int			ft_advanced_sort_wordtab(char **tab, int (*cmp)())
{
	int	count;
	int	i;
	int	save;

	count = 1;
	i = escape_option(tab);
	save = i;
	while (count)
	{
		count = 0;
		while (tab[i + 1])
		{
			if (cmp(tab[i], tab[i + 1]) > 0)
			{
				ft_swap(&tab[i], &tab[i + 1]);
				count = 1;
			}
			++i;
		}
		i = save;
	}
	return (save);
}
