/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/22 15:56:46 by gubourge          #+#    #+#             */
/*   Updated: 2016/03/10 18:36:20 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && --n > 0)
		++i;
	if (s1[i] > s2[i])
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else if (s1[i] < s2[i])
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
