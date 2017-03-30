/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 16:12:41 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/30 19:26:22 by gubourge         ###   ########.fr       */
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

	if (term->flag == 1)
	{
		dup2((term->pipefd)[1], 1);
		close((term->pipefd)[0]);
	}
	cmd = find_cmd(param[0], env);
//	dprintf(2, "%s\n", cmd);
	execve(cmd, param, *env);
	ft_putstr_fd(param[0], 2);
	ft_putstr_fd(CMD_ERROR_MSG, 2);
	exit(1);
}

int		exec_cmd(char **param, t_term *term, char ***env)
{
	if ((g_child = fork()) == -1)
	{
		ft_putstr_fd("Error: in ft_minishell.c: fork didn't work\n", 2);
		return (-1);
	}
	if (g_child == 0)
	{
		exec_cmd_bis(param, term, env);
	}
	if (signal(SIGTSTP, quit_handler) == SIG_ERR)
		return (-1);
	waitpid(g_child, NULL, 0);
	if (term->flag == 1)
	{
		dup2((term->pipefd)[0], 0);
		close((term->pipefd)[1]);
	}
	return (0);
}

/*int		command_loop(char ***env, char **param, int flag,
			     char **new_env)
{
  int		i;
  char		**path;
  char		*pathname;

  i = 0;
  if ((check_builtins_and_path(param, env, &pathname)) == 1)
    return (0);
  path = sh_wordtab(pathname);
  while (path[i] != NULL &&
	 access((pathname = make_pathname(path[i], param[0])), F_OK) != 0)
    ++i;
  if (path_verify(param[0], path, i) == -1)
    return (-1);
  if (!vfork())
    {
      if (kill_verify(param) == -1)
	return (0);
      if (flag == 2 || flag == 3)
      	execve(pathname, param, new_env);
      else
	execve(pathname, param, *env);
      exit(1);
    }
  my_wait(flag, i);
  return (0);
}*/

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

int		command_exe(char **param, t_term *term, t_builtin *builtin)
{
	int		ret;
	int		i;

	term->sv_0 = dup(0);
	term->sv_1 = dup(1);
	term->flag = 0;
	i = 0;
	if (term)
		if (tcsetattr(0, TCSADRAIN, &(term->old_termios)) == -1)
			return (-1);
	while (param[i])
    {
//		dprintf(2, "%s\n", param[i]);
		ret = command_exe_loop(param, i, term, builtin);
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
	{
		exec_cmd(&param[find_last_cmd(param, i)], term, &(term->env));
	}
	if (ret == 0 || ret == 3)
	{
		exec_cmd(&param[find_last_cmd(param, i - 1)], term, &(term->env));
//		dprintf(2, "OK\n");
	}
	dup2(term->sv_0, 0);
	dup2(term->sv_1, 1);
	if (term)
		if (tcsetattr(0, TCSADRAIN, &(term->new_termios)) == -1)
			return (-1);
	return (1);
}
