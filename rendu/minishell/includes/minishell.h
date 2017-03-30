/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 14:31:51 by gubourge          #+#    #+#             */
/*   Updated: 2017/01/19 14:58:32 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# define BUFF_SIZE 4096
# define NB_BUILTIN 6
# define BUILTIN "echo:cd:setenv:unsetenv:env:exit"
# define VAR_PATH "PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin"

typedef	int			(*t_func_ptr)(char **param, char ***env);

typedef struct		s_builtin
{
	char			**tab_built;
	t_func_ptr		tab_func[NB_BUILTIN + 1];
}					t_builtin;

typedef struct		s_env
{
	char			*tab[3];
	char			opt_p;
	char			*tmp;
}					t_env;

int					cp_env(char ***env_cp, char **env);
int					ft_minishell(t_builtin *builtin, char ***env);
int					exec_cmd(char **param, char ***env);
char				*find_cmd(char *find, char ***env);
char				**find_my(char ***env, char *str);
int					ft_str_is_alpha(char *str);
int					is_built_in(t_builtin *builtin, char **param, char ***env);
int					ft_get_line(const int fd, char **line);
int					ft_echo(char **param, char ***env);
int					ft_cd(char **param, char ***env);
int					cd_go_to(char *new_path, char ***env);
int					cd_new_pwd(char *new_pwd, char ***env);
int					cd_error(char *param);
int					ft_setenv(char **param, char ***env);
int					ft_env(char **param, char ***env);
int					env_u(char ***env, t_env *env_built, char **param, int *i);
int					env_p(char **param, t_env *env_built, int *i);
int					env_p_bis(t_env *env_built, char **param, char opt_p);
int					ft_unsetenv(char **param, char ***env);
int					ft_exit(char **param, char ***env);
void				ft_shlvl(char **var, char ***env);
void				quit_handler(int sig);

#endif
