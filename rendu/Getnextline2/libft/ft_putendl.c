/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:09:39 by gubourge          #+#    #+#             */
/*   Updated: 2016/03/10 15:21:42 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putendl(char const *s)
{
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}