/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semi_colon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:05:33 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/29 17:38:07 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mnsh.h"

void		sc_loop(char **param, t_term *term, int i)
{
	int		j;
	int		ret;

	param[i] = NULL;
	command_loop(&param[find_last_cmd(param, i - 1)], term);
}

int		sc_exe(char **param, t_term *term, int i)
{
	sc_loop(param, term, i);
	return (1);
}

int		is_sc(char **param)
{
	if (param && param[0])
		if (ft_strcmp(param[0], ";") == 0)
			return (1);
	return (-1);
}
