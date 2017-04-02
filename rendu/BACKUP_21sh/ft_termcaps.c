/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 17:37:24 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/20 19:28:04 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <termcap.h>
#include <term.h>
#include <sys/ioctl.h>

// redimensionnement de la fenetre a gerer pour le curseur

int		ft_getnblen(int nb)
{
	long int	count;
	int			cpt;

	cpt = 1;
	count = 10;
	while (count <= nb)
	{
		count *= 10;
		cpt++;
	}
	return (cpt);
}

int		ft_getch(char *str)
{
	int	nb;
	int	i;

	if (!str)
		return (0);
	i = -1;
	nb = 0;
	while (str[++i])
	{
		nb *= ft_power(10, ft_getnblen((int)str[i]));
		nb += (int)str[i];
	}
	if (nb < 0)
		return (0);
	return (nb);
}

int		ft_outc(int c)
{
	ft_putchar(c);
	return (0);
}

void	find_arrow(t_func_cursor *func_cursor, int nb, t_term *term, char *line)
{
	if (nb == KEY_ALT_LEFT)
		ft_key_alt_left(term, line);
	else if (nb == KEY_ALT_RIGHT)
		ft_key_alt_right(term, line);
	else if (nb == KEY_ALT_UP)
		ft_key_alt_up(term, line);
	else if (nb == KEY_ALT_DOWN)
		ft_key_alt_down(term, line);
	else
	{
		if ((nb ^ MASK) > 256)
			return ;
		if (func_cursor[nb ^ MASK])
			func_cursor[nb ^ MASK](term, line);
	}
}

int		see_bind(t_func_term *func_term,
		t_func_cursor *func_cursor, char **line, t_term *term)
{
	int		ret;
	char	buffer[4];
	int		nb;

	term->pos_x = 0;
	term->pos_y = 0;
	term->area = NULL;
	term->line_length = 0;
	if (!(*line = (char *)malloc(sizeof(char) * (LINE_SIZE + 1))))
		return (-1);
	ft_bzero(*line, LINE_SIZE + 1);
	while (1)
	{
		ret = read(0, buffer, 4);
		buffer[ret] = 0;
		if ((nb = ft_getch(buffer)) > 256)
			find_arrow(func_cursor, nb, term, *line);
		else if (func_term[nb])
			if ((ret = func_term[nb](term, line, buffer[0])) > 0)
				return (ret);
	}
	return (0);
}

void	init_func_term(t_func_term *func_term)
{
	int		i;

	i = -1;
	while (++i < 257)
		func_term[i] = &ft_key;
	func_term[KEY_DEL] = &ft_key_del;
	func_term[CTRL_D] = &ft_key_ctrl_d;
	func_term[CTRL_C] = &ft_key_ctrl_c;
	func_term[CTRL_K] = &ft_key_ctrl_k;
	func_term[CTRL_Y] = &ft_key_ctrl_y;
	func_term[CTRL_W] = &ft_key_ctrl_w;
	func_term[CTRL_U] = &ft_key_ctrl_u;
	func_term[KEY_ENTER] = &ft_key_enter;
}

void	init_func_cursor(t_func_cursor *func_cursor)
{
	int		i;

	i = -1;
	while (++i < 257)
		func_cursor[i] = NULL;
	func_cursor[KEY_UP ^ MASK] = &ft_key_up;
	func_cursor[KEY_DOWN ^ MASK] = &ft_key_down;
	func_cursor[KEY_LEFT ^ MASK] = &ft_key_left;
	func_cursor[KEY_RIGHT ^ MASK] = &ft_key_right;
	func_cursor[KEY_END ^ MASK] = &ft_key_end;
	func_cursor[KEY_HOME ^ MASK] = &ft_key_home;
}

int		ft_termcaps(char **line, t_term *term)
{
	t_func_term		func_term[257];
	t_func_cursor	func_cursor[257];

	init_func_cursor(func_cursor);
	init_func_term(func_term);
	return (see_bind(func_term, func_cursor, line, term));
}
