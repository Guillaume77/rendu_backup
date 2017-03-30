/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keycode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:36:00 by gubourge          #+#    #+#             */
/*   Updated: 2017/03/15 18:55:49 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define KEY_UP 279165
#define KEY_DOWN 279166
#define KEY_RIGHT 279167
#define KEY_LEFT 279168

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <term.h>
#include <signal.h>
#include <string.h>

void			quit_handler(int sig)
{
	if (sig == SIGTSTP)
		exit(1);
}

int		main(void)
{
	char	buff[4];
	int		ret;
	char			*name_term;
	struct termios	term;
	struct termios	old_term;

	if (signal(SIGINT, quit_handler) == SIG_ERR)
		return (-1);
	if (signal(SIGTSTP, quit_handler) == SIG_ERR)
		return (-1);
	if (tcgetattr(0, &old_term) == -1)
		return (-1);
	term = old_term;
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	while (1)
	{
		read(0, buff, 4);
		printf("keycode is : %d %d %d %d\n", buff[0], buff[1], buff[2], buff[3]);
		buff[0] = 0;
		buff[1] = 0;
		buff[2] = 0;
		buff[3] = 0;
	}
	if (tcsetattr(0, TCSANOW, &old_term) == -1)
		return (-1);
	return (0);
}
