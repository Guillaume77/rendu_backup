/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_last_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 18:11:49 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/30 16:05:26 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		find_last_cmd(char **param, int i)
{
	if (i < 0)
		return (0);
	while (param[i] && i > 0)
		--i;
	if (param[i] == NULL && param[i + 1])
		return (i + 1);
	else
		return (i);
}
