/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 17:45:28 by gubourge          #+#    #+#             */
/*   Updated: 2017/01/19 14:55:46 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void		ft_shlvl(char **var, char ***env)
{
	char	*cmd[3];
	char	*tmp;
	int		nb;

	if (!var)
		return ;
	tmp = &(*var)[ft_strlen("SHLVL") + 1];
	nb = ft_atoi(tmp);
	nb += 1;
	cmd[0] = 0;
	cmd[1] = ft_strdup("SHLVL");
	cmd[2] = ft_itoa(nb);
	ft_setenv(cmd, env);
	free(cmd[1]);
	free(cmd[2]);
}
