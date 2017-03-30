/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semi_colon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:05:33 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/30 18:59:29 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"

void		sc_loop(char **param, t_term *term, int i)
{
	exec_cmd(&param[find_last_cmd(param, i - 1)], term, &(term->env));
	dup2(term->sv_0, 0);
	dup2(term->sv_1, 1);
}

int		sc_exe(char **param, t_term *term, int i)
{
	param[i] = NULL;
	if (i <= 0 || !param[i - 1])
		return (1);
	sc_loop(param, term, i);
	return (0);
}

int		is_sc(char **param)
{
	if (param && param[0])
		if (ft_strcmp(param[0], ";") == 0)
			return (1);
	return (-1);
}
