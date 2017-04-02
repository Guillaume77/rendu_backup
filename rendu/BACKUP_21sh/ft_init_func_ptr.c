/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_func_ptr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 17:16:32 by gubourge          #+#    #+#             */
/*   Updated: 2017/04/02 16:21:48 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_is_sep(t_is_sep *is_sep)
{
	is_sep[0] = &is_sc;
	is_sep[1] = &d_l_is_redirection;
	is_sep[2] = &d_is_redirection;
	is_sep[3] = &is_pipe;
	is_sep[4] = &l_is_redirection;
	is_sep[5] = &is_redirection;
	is_sep[6] = NULL;
}

void		init_exec(t_exec *exec)
{
	exec[0] = &sc_exe;
	exec[1] = &d_l_redirection_exe;
	exec[2] = &d_redirection_exe;
	exec[3] = &pipe_exe;
	exec[4] = &l_redirection_exe;
	exec[5] = &redirection_exe;
	exec[6] = NULL;
}

void		init_tab_func(t_term *term)
{
	term->tab_func[0] = &ft_echo;
	term->tab_func[1] = &ft_cd;
	term->tab_func[2] = &ft_setenv;
	term->tab_func[3] = &ft_unsetenv;
	term->tab_func[4] = &ft_env;
	term->tab_func[5] = &ft_exit;
	term->tab_func[6] = NULL;
}

int			init_builtin(t_builtin *builtin, t_term *term)
{
	if (!(term->tab_built = ft_strsplit(BUILTIN, ':')))
		return (-1);
	init_tab_func(term);
	init_exec(builtin->exec);
	init_is_sep(builtin->is_sep);
	return (0);
}

