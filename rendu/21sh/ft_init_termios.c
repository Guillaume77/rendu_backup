/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_termios.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:37:20 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/13 17:05:51 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <term.h>
#include <stdlib.h>

int		ft_init_termios(t_term *term)
{
	if (tgetent(NULL, getenv("TERM")) == -1)
		return (-1);
	if (tcgetattr(0, &(term->old_termios)) == -1)
		return (-1);
	term->new_termios = term->old_termios;
	term->new_termios.c_lflag &= ~(ICANON | ECHO | ISIG); // Met le terminal en mode noncanonique. Les touches tapées ne s'inscriront plus dans le terminal. les signaux sont supprimes.
//	term->old_termios.c_lflag &= (ICANON | ECHO); // Met le terminal en mode canonique. Les touches tapées ne s'inscriront plus dans le terminal. les signaux sont supprimes.
	term->new_termios.c_cc[VMIN] = 0; // Nombre de touche entre chaque read.
	term->new_termios.c_cc[VTIME] = 20;
	if (tcsetattr(0, TCSADRAIN, &(term->new_termios)) == -1)
		return (-1);
	return (0);
}
