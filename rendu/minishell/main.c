/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 16:42:06 by gubourge          #+#    #+#             */
/*   Updated: 2017/01/19 17:20:15 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include "minishell.h"

void			quit_handler(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n$>", 1);
}

static void		init_tab_func(t_builtin **builtin)
{
	(*builtin)->tab_func[0] = &ft_echo;
	(*builtin)->tab_func[1] = &ft_cd;
	(*builtin)->tab_func[2] = &ft_setenv;
	(*builtin)->tab_func[3] = &ft_unsetenv;
	(*builtin)->tab_func[4] = &ft_env;
	(*builtin)->tab_func[5] = &ft_exit;
	(*builtin)->tab_func[6] = NULL;
}

static int		init_builtin(t_builtin **builtin)
{
	if (!(*builtin = (t_builtin *)malloc(sizeof(t_builtin))))
		return (-1);
	if (!((*builtin)->tab_built = ft_strsplit(BUILTIN, ':')))
		return (-1);
	init_tab_func(builtin);
	return (0);
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
	struct termios	old_termios;
	struct termios	new_termios;
	t_builtin		*builtin;
	char			**env_cp;
	int				ret;

	ac++;
	av++;
	if (cp_env(&env_cp, env) == -1)
		return (-1);
	if (init_builtin(&builtin) == -1)
		return (-1);
	ft_shlvl(find_my(&env_cp, "SHLVL"), &env_cp);
	ft_putstr_fd("$>", 1);
	if (signal(SIGINT, quit_handler) == SIG_ERR)
		return (-1);
	tcgetattr(0, &old_termios);
	new_termios = old_termios;
//	new_termios.c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, &new_termios);
	ret = ft_minishell(builtin, &env_cp);
	ft_freetab(builtin->tab_built, ft_tablen(builtin->tab_built));
	free(builtin);
	ft_freetab(env_cp, ft_tablen(env_cp));
	tcsetattr(0, TCSANOW, &old_termios);
	return (ret);
}
