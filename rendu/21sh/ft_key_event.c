/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:07:25 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/01 17:22:44 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <termcap.h>
#include <term.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>

void		ft_key_bis(t_term *term, char *line, char c, char *ptr_c)
{
	int		i;
	char	*tmp;
	char	*tmp2;

//	tputs(ptr_c, 1, &ft_outc);
	tmp2 = ft_strdup(line);
	tmp2[term->pos_x] = 0;
	tmp = ft_strjoin(tmp2, ptr_c);
	tmp = ft_strjoin(tmp, &line[term->pos_x]);
	ft_strcpy(line, tmp);
	i = term->pos_x;
	while (line[term->pos_x])
	{
		tputs(tgetstr("sc", &(term->area)), 1, &ft_outc);
		ptr_c[0] = line[term->pos_x];
		tputs(ptr_c, 1, &ft_outc);
//		term->pos_x++;
		tputs(tgetstr("rc", &(term->area)), 1, &ft_outc);
		ft_key_right(term, line, c);
	}
	while (term->pos_x > i)
		ft_key_left(term, line ,c);
//	tputs(&line[term->pos_x], 1, &ft_outc);
	ft_key_right(term, line, c);
	free(tmp);
	free(tmp2);
}

void		ft_key(t_term *term, char *line, char c)
{
	char			ptr_c[2];

	if (!ft_isprint((int)c))
		return ;
	ptr_c[0] = c;
	ptr_c[1] = 0;
	if (line[term->pos_x] != 0)
		ft_key_bis(term, line, c, ptr_c);
	else
	{
		tputs(tgetstr("sc", &(term->area)), 1, &ft_outc);
		tputs(ptr_c, 1, &ft_outc);
		line[term->pos_x] = c;
		line[term->pos_x + 1] = 0;
		tputs(tgetstr("rc", &(term->area)), 1, &ft_outc);
		ft_key_right(term, line, c);
	}
}

void		ft_key_right(t_term *term, char *line, char c)
{
	struct winsize	argp;
	int				tmp_pos;

	if (term->pos_x < ft_strlen(line))
	{
		if ((ioctl(0, TIOCGWINSZ, &argp)) == -1)
			return ;
		term->pos_y = term->pos_x /*+ ft_strlen(PROMPT)*/ / argp.ws_col;
		tmp_pos = (term->pos_x + 1) /*+ ft_strlen(PROMPT)*/ - (term->pos_y * argp.ws_col);
		if (tmp_pos == argp.ws_col)
		{
			term->res = tgetstr("sf", &(term->area));
			tputs(term->res, 1, &ft_outc);
			ft_putchar('\r');
		}
		else
		{
			term->res = tgetstr("nd", &(term->area));
			tputs(term->res, 1, &ft_outc);
		}
		(term->pos_x)++;
	}
}

void		ft_key_more_right(t_term *term, char *line, char c)
{
	struct winsize	argp;
	int				tmp_pos;

	if ((ioctl(0, TIOCGWINSZ, &argp)) == -1)
		return ;
	term->pos_y = term->pos_x /*+ ft_strlen(PROMPT)*/ / argp.ws_col;
	tmp_pos = (term->pos_x + 1) /*+ ft_strlen(PROMPT)*/ - (term->pos_y * argp.ws_col);
	while ((tmp_pos < argp.ws_col) && (term->pos_x < ft_strlen(line)))
	{
		term->res = tgetstr("nd", &(term->area));
		tputs(term->res, 1, &ft_outc);
		(term->pos_x)++;
		(tmp_pos)++;
	}
}

void		ft_key_left(t_term *term, char *line, char c)
{
	struct winsize	argp;
	int				tmp_pos;

	if (term->pos_x > 0)
	{
		if ((ioctl(0, TIOCGWINSZ, &argp)) == -1)
			return ;
		term->pos_y = term->pos_x /*+ ft_strlen(PROMPT)*/ / argp.ws_col;
		tmp_pos = (term->pos_x + 1) /*+ ft_strlen(PROMPT)*/ - (term->pos_y * argp.ws_col);
		if (tmp_pos == 1)
		{
			term->res = tgetstr("sr", &(term->area));
			tputs(term->res, 1, &ft_outc);
			term->pos_x -= argp.ws_col;
			ft_key_more_right(term, line, c);
		}
		else
		{
			(term->pos_x)--;
			term->res = tgetstr("le", &(term->area));
			tputs(term->res, 1, &ft_outc);
		}
	}
}
