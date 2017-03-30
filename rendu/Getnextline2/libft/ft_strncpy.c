/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/22 12:03:20 by gubourge          #+#    #+#             */
/*   Updated: 2015/10/26 15:54:52 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char		*ft_strncpy(char *dest, char *src, unsigned int n)
{
	int		i;

	i = 0;
	while (src[i] && n > 0)
	{
		dest[i] = src[i];
		++i;
		n--;
	}
	while (n > 0)
	{
		dest[i] = 0;
		++i;
		--n;
	}
	return (dest);
}
