/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 17:22:21 by gubourge          #+#    #+#             */
/*   Updated: 2016/10/19 15:24:01 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define S_a 1
# define S_R 2
# define S_l 4
# define S_t 8
# define S_r 16
# define SIX_M 15778800

#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

typedef struct		s_list
{
	struct s_list	*next;
	char			*name;
	char			*usr_name;
	char			*grp_name;
	char			*path;
	struct stat		stats;
}					t_list;

typedef int (*func_ptr)(const t_list *, const t_list *);

void		ft_putnbr(long long int n);
void		ft_list_push_back(t_list **begin_list, struct dirent *entry, const char *path);
void		ft_list_reverse(t_list **begin_list);
t_list		*ft_create_elem(struct dirent *entry, const char *path);
void		ft_list_sort(t_list **begin_list, char op, func_ptr *func_strcmp);
void		ft_list_remove_if(t_list **begin_list);
void		ft_free_list(t_list **begin_list);
void		ft_free_all(t_list *list);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strcmp_modify(const t_list *s1, const t_list *s2);
int			ft_strcmp_r(const t_list *s1, const t_list *s2);
int			ft_strcmp_t(const t_list *s1, const t_list *s2);
int			ft_strcmp_rt(const t_list *s1, const t_list *s2);
int			ft_advanced_sort_wordtab(char **tab, int (*cmp)());
void		ft_n_a(t_list **list);
int			ft_take_op(char **av, char *op);
void		ft_ls(char *av, char op, int no_path, func_ptr *func_strcmp);
char		*ft_strdup(const char *src);
void		ft_ls_print(char *av);
int			no_path(char **av);
int			ft_power(int nb, int power);
void		print_list_l(t_list **list);
char		*ft_itoa(int n);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strcat(char *dest, const char *src);
size_t		ft_strlen(const char *s);
void		init_func_ptr(func_ptr *func_strcmp);
int			print_date(struct stat stats);
void		print_mode(int perm);
void		print_perms(int perm);
void		print_padd(int padd, int size);
void		print_list(t_list **list, char op);

#endif
