/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 16:42:06 by gubourge          #+#    #+#             */
/*   Updated: 2017/04/02 17:28:56 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include "minishell.h"

pid_t			g_child;

void			quit_handler(int sig)
{
//	if (sig == SIGINT)
	ft_putchar_fd('\n', 1);
	if (sig == SIGTSTP)
		kill(g_child, SIGKILL);
}

int				cp_env(char ***env_cp, char **env)
{
	int		i;

	i = 0;
	if (!(*env_cp = (char **)malloc(sizeof(char *) * (ft_tablen(env) + 1))))
		return (-1);
	while (env[i])
	{
		if (!((*env_cp)[i] = ft_strdup(env[i])))
			return (-1);
		++i;
	}
	(*env_cp)[i] = NULL;
	return (0);
}

int				main(int ac, char **av, char **env)
{
	t_term			term;
	t_builtin		builtin;
	int				ret;

	ac++;
	av++;
	term.i_hsty = 0;
	term.cp = NULL;
	if (!(term.prompt = ft_strdup(PROMPT)))
		return (-1);
	ft_tabbzero((void **)term.history, MAX_HISTORY);
	ft_tabbzero((void **)term.tmp_history, MAX_HISTORY + 1);
	if (cp_env(&(term.env), env) == -1)
		return (-1);
	if (init_builtin(&builtin, &term) == -1)
		return (-1);
	ft_shlvl(find_my(&(term.env), "SHLVL"), &(term.env));
	if (signal(SIGINT, quit_handler) == SIG_ERR)
		return (-1);
	ft_putstr_fd("$>", 1);
	if (ft_init_termios(&term) == -1)
		return (-1);
	ret = ft_minishell(&builtin, &term);
	ft_freetab(term.tab_built, ft_tablen(term.tab_built));
	ft_freetab(term.env, ft_tablen(term.env));
	ft_freehistory(&term);
	free(term.prompt);
	if (tcsetattr(0, TCSANOW, &(term.old_termios)) == -1)
		return (-1);
	return (ret);
}
