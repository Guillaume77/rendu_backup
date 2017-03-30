/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:11:23 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/29 18:10:18 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
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
int		exec_cmd(char **param, t_term *term)
{
	char	*cmd;

	if ((g_child = fork()) == -1)
	{
		ft_putstr_fd("Error: in ft_minishell.c: fork didn't work\n", 2);
		return (-1);
	}
	if (g_child == 0)
	{
		cmd = find_cmd(param[0], &(term->env));
		if (term)
			if (tcsetattr(0, TCSADRAIN, &(term->old_termios)) == -1)
				return (-1);
		execve(cmd, param, term->env);
		ft_putstr_fd(param[0], 2);
		ft_putstr_fd(CMD_ERROR_MSG, 2);
		exit(-1);
	}
	if (signal(SIGTSTP, quit_handler) == SIG_ERR)
		return (-1);
	waitpid(g_child, NULL, 0);
	if (term)
		if (tcsetattr(0, TCSADRAIN, &(term->new_termios)) == -1)
			return (-1);
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
}
*/
int		command_exe_loop(char **param, int i, t_term *term)
{
	int		j;
	int		save1;
	int		ret;

	ret = 1;
	save1 = dup(1);
	j = 0;
	while (term->buitlin.is_sep[j] && term->builtin.is_sep[j](&(param[i])) <= 0)
		++j;
	if (j < NB_SEP)
		ret = term->builtin.exec[j](param, term, i);
	dup2(save1, 1);
	return (ret);
}

int		command_exe(char **param, t_term *term)
{
	int		ret;
	int		i;
	int		save0;

	save0 = dup(0);
	i = 0;
	while (param[i])
    {
		ret = command_exe_loop(param, i, term);
		if ((ret == 3 || ret == 2) && param[i + 2])
			++i;
		++i;
    }
	if (ret == 2)
		command_loop(&(term->env), &param[find_last_cmd(param, i)], 1, NULL);
	if (ret == 1 || ret == 3)
		command_loop(&(term->env), &param[find_last_cmd(param, i - 1)], 1, NULL);
	dup2(save0, 0);
	return (1);
}
