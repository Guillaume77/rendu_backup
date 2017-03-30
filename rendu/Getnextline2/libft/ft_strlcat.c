/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 14:07:50 by gubourge          #+#    #+#             */
/*   Updated: 2016/03/03 14:57:34 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int			ft_strlen(char *str)
{
	int				i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

unsigned int		ft_strlcat(char *dest, char *src, unsigned int size)
{
	int				i;
	int				j;
	unsigned int	size_dest;
	unsigned int	save;

	j = 0;
	size_dest = ft_strlen(dest);
	save = ft_strlen(src);
	if (save + size >= save + size_dest)
		save += size_dest;
	else
		save += size;
	i = size_dest;
	while (size > (size_dest + 1) && src[j])
	{
		dest[i] = src[j];
		++i;
		++j;
		size--;
	}
	dest[i] = 0;
	return (save);
}
