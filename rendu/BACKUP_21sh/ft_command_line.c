/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 16:12:41 by gubourge          #+#    #+#             */
/*   Updated: 2017/04/02 17:07:02 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

pid_t	g_child;

/*static int	check_builtins_and_path(char **param, char ***env,
					char **pathname)
{
  if (check_builtins(param, env) == 1)
    return (1);
  if ((*pathname = path_finder(*env)) == NULL)
    return (1);
  return (0);
}
*/

int		exec_cmd_bis(char **param, t_term *term, char ***env)
{
	char	*cmd;

	if (term && term->flag == 1)
	{
		dup2((term->pipefd)[1], 1);
		close((term->pipefd)[0]);
	}
	cmd = find_cmd(param[0], env);
	execve(cmd, param, *env);
	ft_putstr_fd(param[0], 2);
	ft_putstr_fd(CMD_ERROR_MSG, 2);
	exit(1);
	return (0);
}

int		if_builtin(char **param, char ***env, t_term *term)
{
	int	ret;

	if (!term)
		return (-2);
	if (!param || !param[0])
		return (-1);
	ret = is_built_in(term, param, env);
	if (ft_strcmp(param[0], "exit") == 0 && ret != -2)
	{
		term->flag = 2;
		return (ret);
	}
	return (ret);
}

int		exec_cmd(char **param, t_term *term, char ***env)
{
	int	ret;

	if ((ret = if_builtin(param, env, term)) != -2)
		return (ret);
	if ((g_child = fork()) == -1)
	{
		ft_putstr_fd("Error: in exec_cmd: fork didn't work\n", 2);
		return (-1);
	}
	if (g_child == 0)
	{
		return (exec_cmd_bis(param, term, env));
	}
	if (signal(SIGTSTP, quit_handler) == SIG_ERR)
		return (-1);
	waitpid(g_child, NULL, 0);
	if (term && term->flag == 1)
	{
		dup2((term->pipefd)[0], 0);
		close((term->pipefd)[1]);
	}
	else if (term && term->flag == 2)
		exit(1);
	return (0);
}

int		command_exe_loop(char **param, int i, t_term *term, t_builtin *builtin)
{
	int		j;
	int		ret;

	ret = 0;
	j = 0;
	while (builtin->is_sep[j] && builtin->is_sep[j](&(param[i])) <= 0)
		++j;
	if (j < NB_SEP)
		ret = builtin->exec[j](param, term, i);
	return (ret);
}

int		set_termcaps(t_term *term, int flag)
{
	if (!term)
		return (-1);
	if (flag == 1)
	{
		if (tcsetattr(0, TCSADRAIN, &(term->old_termios)) == -1)
			return (-1);
	}
	else if (flag == 0)
	{
		if (tcsetattr(0, TCSADRAIN, &(term->new_termios)) == -1)
			return (-1);
	}
	return (0);
}

int		command_exe(char **param, t_term *term, t_builtin *builtin)
{
	int		ret;
	int		i;

	term->sv_0 = dup(0);
	term->sv_1 = dup(1);
	term->flag = 0;
	i = 0;
	if (set_termcaps(term, 1) == -1)
		return (-1);
	while (param[i])
    {
//		dprintf(2, "%s\n", param[i]);
		ret = command_exe_loop(param, i, term, builtin);
		if (term->flag == 2)
			return (ret);
		if ((ret == 3 || ret == 2) && param[i + 2])
			++i;
		++i;
		if (term->flag == 1)
		{
			term->flag = 0;
			dup2(term->sv_1, 1);
		}
    }
//	exec_cmd(&param[find_last_cmd(param, i)], term, &(term->env));
	if (ret == 2)
		ret = exec_cmd(&param[find_last_cmd(param, i)], term, &(term->env));
	if (ret == 0 || ret == 3)
		ret = exec_cmd(&param[find_last_cmd(param, i - 1)], term, &(term->env));
	dup2(term->sv_0, 0);
	dup2(term->sv_1, 1);
	if (term->flag == 2)
		return (ret);
	if (set_termcaps(term, 0) == -1)
		return (-1);
	return (1);
}
