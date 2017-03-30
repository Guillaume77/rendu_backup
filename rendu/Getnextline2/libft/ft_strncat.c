/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 13:51:10 by gubourge          #+#    #+#             */
/*   Updated: 2015/10/31 15:55:53 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char		*ft_strncat(char *dest, char *src, int nb)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (dest[i])
		++i;
	while (nb > 0 && src[j])
	{
		dest[i] = src[j];
		++j;
		++i;
		nb--;
	}
	dest[i] = 0;
	return (dest);
}
