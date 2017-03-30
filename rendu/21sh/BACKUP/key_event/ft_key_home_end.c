/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_home_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 14:35:29 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/07 17:00:24 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_key_home(t_term *term, char *line)
{
	line++;
	ft_cursor_more_left(term);
}

void		ft_key_end(t_term *term, char *line)
{
	ft_cursor_more_right(term, ft_strlen(line));
}
