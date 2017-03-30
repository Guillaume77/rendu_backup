/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:11:15 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/22 15:12:57 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "mnsh.h"

int	is_ee_separator(char **param)
{
  if (param && param[0] != NULL && param[1] != NULL)
    {
      if (my_strcmp(param[0], "&") == 0 &&
	  my_strcmp(param[1], "&") == 0)
	return (1);
    }
  return (-1);
}

int	is_oo_separator(char **param)
{
  if (param && param[0] != NULL && param[1] != NULL)
    {
      if (!my_strcmp(param[0], "|") && !my_strcmp(param[1], "|"))
	return (1);
    }
  return (-1);
}

int	ee_separator_exe(char **param, char ***env, int i, t_term *term)
{
  int	cmd_res;
  int	cmd;

  cmd_res = 0;
  cmd = 0;
  param[i] = NULL;
  param[i + 1] = NULL;
  if (param[i - 1] != NULL)
    {
      cmd = command_loop(env, &param[find_last_cmd(param, i - 1)], 0, *env);
      cmd_res = my_wait(1, cmd_res);
    }
  if (cmd_res == 0 && cmd == 0)
    return (2);
  return (0);
}

int	oo_separator_exe(char **param, char ***env, int i)
{
  int	cmd_res;
  int	cmd;

  cmd = 0;
  cmd_res = 0;
  param[i] = NULL;
  param[i + 1] = NULL;
  if (param[i - 1] != NULL)
    {
      cmd = command_loop(env, &param[find_last_cmd(param, i - 1)], 0, *env);
      cmd_res = my_wait(1, cmd_res);
    }
  if (cmd_res == 0 && cmd == -1)
    return (2);
  return (0);
}
