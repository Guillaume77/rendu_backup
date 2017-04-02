/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:07:25 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/20 17:04:23 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <termcap.h>
#include <term.h>
#include <signal.h>
#include <stdlib.h>

int			ft_remalloc_line(char **line, int *line_length, int current_size)
{
	int		nb;
	char	*tmp;

	nb = current_size / LINE_SIZE;
	if (nb <= *line_length)
		return (0);
	while (nb > *line_length)
		(*line_length)++;
	if (!(tmp = (char *)malloc(sizeof(char) *
		(LINE_SIZE * (*line_length + 1)))))
		return (-1);
	ft_strcpy(tmp, *line);
	free(*line);
	*line = tmp;
	return (0);
}

void		ft_key_bis2(t_term *term, char **line, char *ptr_c)
{
	while ((*line)[term->pos_x])
	{
		tputs(tgetstr("sc", &(term->area)), 1, &ft_outc);
		ptr_c[0] = (*line)[term->pos_x];
		tputs(ptr_c, 1, &ft_outc);
		tputs(tgetstr("rc", &(term->area)), 1, &ft_outc);
		ft_key_right(term, *line);
	}
}

int			ft_key_bis(t_term *term, char **line, char *ptr_c)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	if (!(tmp2 = ft_strdup(*line)))
		return (-1);
	tmp2[term->pos_x] = 0;
	if (!(tmp3 = ft_strjoin(tmp2, ptr_c)))
		return (-1);
	if (!(tmp = ft_strjoin(tmp3, &((*line)[term->pos_x]))))
		return (-1);
	if (ft_remalloc_line(line, &(term->line_length), ft_strlen(tmp)) == -1)
		return (-1);
	ft_strcpy(*line, tmp);
	i = term->pos_x;
	ft_key_bis2(term, line, ptr_c);
	while (term->pos_x > i)
		ft_key_left(term, *line);
	ft_key_right(term, *line);
	free(tmp);
	free(tmp2);
	free(tmp3);
	return (0);
}

int			ft_key_print(t_term *term, char *line, char c)
{
	char			ptr_c[2];

	if (!ft_isprint((int)c))
		return (0);
	ptr_c[0] = c;
	ptr_c[1] = 0;
	tputs(tgetstr("sc", &(term->area)), 1, &ft_outc);
	tputs(ptr_c, 1, &ft_outc);
	tputs(tgetstr("rc", &(term->area)), 1, &ft_outc);
	ft_key_right(term, line);
	return (1);
}

int			ft_key(t_term *term, char **line, char c)
{
	char			ptr_c[2];

	if (!ft_isprint((int)c))
		return (0);
	ptr_c[0] = c;
	ptr_c[1] = 0;
	if ((*line)[term->pos_x] != 0)
		return (ft_key_bis(term, line, ptr_c));
	else
	{
		tputs(tgetstr("sc", &(term->area)), 1, &ft_outc);
		tputs(ptr_c, 1, &ft_outc);
		if (ft_remalloc_line(line, &(term->line_length), ft_strlen(*line)) == -1)
			return (-1);
		(*line)[term->pos_x] = c;
		(*line)[term->pos_x + 1] = 0;
		tputs(tgetstr("rc", &(term->area)), 1, &ft_outc);
		ft_key_right(term, *line);
	}
	return (0);
}
