/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 14:53:15 by gubourge          #+#    #+#             */
/*   Updated: 2016/05/18 13:24:01 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

static int simple_string()
{
    char    *line;
    int     out;
    int     p[2];
    char    *str;
    int     gnl_ret;

    str = (char *)malloc(1000 * 1000);
    *str = '\0';
    strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dol\
or. Suspendisse augue augue, tempus");
    strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dol\
or. Suspendisse augue augue, tempus");
    strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dol\
or. Suspendisse augue augue, tempus");
    out = dup(1);
    pipe(p);
    dup2(p[1], 1);

    write(1, str, strlen(str));
    close(p[1]);
    dup2(out, 1);
    gnl_ret = get_next_line(p[0], &line);
	printf("%s\n", line);
	printf("%s\n", str);
    if (strcmp(line, str) == 0)
		printf("NON\n");
	printf("%d = ret\n", gnl_ret);
}

int		main(int ac, char **av)
{
	char	*s;
	int		fd;
	int		i;
	int		ret;

/*	i = 1;
	while (i < ac)
	{
		fd = open(av[i], O_RDONLY);
		while ((ret = get_next_line(fd, &s)) > 0)
		{
			printf("%s\n", s);
			free(s);
		}
		close(fd);
		i++;
	}
*/
	if ((simple_string()) == -1)
		printf("NOPE\n");
	return (0);
}

