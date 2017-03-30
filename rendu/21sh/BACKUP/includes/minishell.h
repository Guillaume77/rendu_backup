/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 14:31:51 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/30 18:12:47 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define PROMPT "$>"
#define KEY_DEL 127
#define KEY_ENTER 10
#define KEY_UP 279165
#define KEY_DOWN 279166
#define KEY_RIGHT 279167
#define KEY_LEFT 279168
#define KEY_END 279170
#define KEY_HOME 279172
#define KEY_ALT_UP 27279165
#define KEY_ALT_DOWN 27279166
#define KEY_ALT_RIGHT 27279167
#define KEY_ALT_LEFT 27279168
#define CTRL_D 4
#define CTRL_C 3
#define CTRL_K 11
#define CTRL_Y 25
#define CTRL_W 23
#define CTRL_U 21
#define MASK 279100

# include "libft.h"
# define BUFF_SIZE 4096
# define NB_BUILTIN 6
# define NB_SEP 6
# define MAX_HISTORY 20
# define LINE_SIZE 400
# define BUILTIN "echo:cd:setenv:unsetenv:env:exit"
# define VAR_PATH "PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin"
# define D_R_G_ERROR_MSG "Missing name for redirect.\n"
# define CMD_ERROR_MSG ": Command not found\n"
# define OPEN_ERROR_MSG "Open error\n"
# define ENV_U_MSG "env: Option requires an argument\n"
# define EXIT_ERROR_MSG "exit: Expression syntax\n"
# define NULL_CMD "Invalid null command\n"
# define UNDEFINED_VAR "Undefined variable\n"
# define CD_ERROR ": No such file or directory\n"
# define MALLOC_ERROR "Memory allocation error\n"

# include <termios.h>
# include <unistd.h>

extern pid_t		g_child;

typedef struct		s_env
{
	char			*tab[3];
	char			opt_p;
	char			*tmp;
}					t_env;

typedef struct		s_term
{
	char			*res;
	char			*area;
	int				pos_x;
	int				pos_y;	
	struct termios	old_termios;
	struct termios	new_termios;
	char			*history[MAX_HISTORY];
	char			*tmp_history[MAX_HISTORY + 1];
	char			*cp;
	int				line_length;
	int				i_hsty;
	char			**env;
	int				flag;
	int				pipefd[2];
	int				sv_0;
	int				sv_1;
}					t_term;

typedef	int			(*t_func_term)(t_term *term, char **line, char c);
typedef	void		(*t_func_cursor)(t_term *term, char *line);
typedef	int			(*t_func_ptr)(char **param, char ***env);
typedef	int			(*t_is_sep)(char **param);
typedef	int			(*t_exec)(char **param, t_term *term, int i);

typedef struct		s_builtin
{
	char			**tab_built;
	t_func_ptr		tab_func[NB_BUILTIN + 1];
	t_is_sep		is_sep[NB_SEP + 1];
	t_exec			exec[NB_SEP + 1];
}					t_builtin;

int					cp_env(char ***env_cp, char **env);
int					ft_init_termios(t_term *term);
int					init_builtin(t_builtin *builtin);
int					ft_minishell(t_builtin *builtin, t_term *term);
char				*ft_ultimate_strdup(char **tab, int length);
char				**ft_parse(char **tab);
int					exec_cmd(char **param, t_term *term, char ***env);
int					command_exe(char **param, t_term *term, t_builtin *builtin);
char				*find_cmd(char *find, char ***env);
int					find_last_cmd(char **param, int i);
char				**find_my(char ***env, char *str);
void				read_output();
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
int					d_is_redirection(char **param);
int					d_redirection_exe(char **param, t_term *term, int i);
int					d_l_is_redirection(char **param);
int					d_l_redirection_exe(char **param, t_term *term, int i);
int					is_pipe(char **param);
int					pipe_exe(char **param, t_term *term, int i);
int					is_redirection(char **param);
int					redirection_exe(char **param, t_term *term, int i);
int					l_is_redirection(char **param);
int					l_redirection_exe(char **param, t_term *term, int i);
int					is_sc(char **param);
int					sc_exe(char **param, t_term *term, int i);
void				quit_handler(int sig);
int					ft_termcaps(char **line, t_term *term);
void				ft_key_right(t_term *term, char *line);
void				ft_key_left(t_term *term, char *line);
void				ft_key_up(t_term *term, char *line);
void				ft_key_down(t_term *term, char *line);
int					ft_key_ctrl_d(t_term *term, char **line, char c);
int					ft_key_ctrl_c(t_term *term, char **line, char c);
int					ft_key_ctrl_k(t_term *term, char **line, char c);
int					ft_key_ctrl_y(t_term *term, char **line, char c);
int					ft_key_ctrl_k(t_term *term, char **line, char c);
int					ft_key_ctrl_w(t_term *term, char **line, char c);
int					ft_key_ctrl_u(t_term *term, char **line, char c);
int					ft_cp_history(t_term *term);
int					ft_put_history(t_term *term, char *line);
void				ft_freehistory(t_term *term);
int					ft_key_print(t_term *term, char *line, char c);
int					ft_key_del(t_term *term, char **line, char c);
void				ft_del_all(t_term *term, char *line);
int					ft_key_enter(t_term *term, char **line, char c);
int					ft_remalloc_line(char **line, int *line_length, int current_size);
int					ft_key(t_term *term, char **line, char c);
void				ft_key_end(t_term *term, char *line);
void				ft_key_home(t_term *term, char *line);
void				ft_key_alt_right(t_term *term, char *line);
void				ft_key_alt_left(t_term *term, char *line);
void				ft_key_alt_up(t_term *term, char *line);
void				ft_key_alt_down(t_term *term, char *line);
void				ft_cursor_left(t_term *term, int tmp_pos, int len_col, int len_line);
void				ft_cursor_right(t_term *term, int tmp_pos, int len_col, int len_line);
void				ft_cursor_more_left(t_term *term);
void				ft_cursor_more_right(t_term *term, int len_line);
int					ft_outc(int c);

#endif
