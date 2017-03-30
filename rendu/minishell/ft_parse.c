/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 17:38:46 by gubourge          #+#    #+#             */
/*   Updated: 2016/11/09 17:54:54 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

static int			check_end_of_line(char *buff)
{
	int		i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (1);
		++i;
	}
	return (0);
}

static char			*ft_strdup_gnl(char *buff)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buff[i])
		++i;
	if (!(dest = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (buff[i] == ' ' || buff[i] == '\t')
		++i;
	while (buff[i] && buff[i] != '\n')
	{
		dest[j] = buff[i];
		++i;
		++j;
	}
	dest[j] = 0;
	free(buff);
	return (dest);
}

static int			do_the_read(const int fd, char **buff)
{
	int		ret;
	char	buffer[BUFF_SIZE + 1];
	char	*tmp;

	if (!(*buff = (char *)malloc(sizeof(char) * 1)))
		return (-1);
	*buff[0] = 0;
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = 0;
		tmp = ft_strdup(*buff);
		free(*buff);
		*buff = ft_strjoin(tmp, buffer);
		free(tmp);
		if (check_end_of_line(*buff))
			return (ret);
	}
	return (ret);
}

int					ft_get_line(const int fd, char **line)
{
	char *buff;

	buff = NULL;
	if (fd < 0)
		return (-1);
	if (do_the_read(fd, &buff) == -1)
	{
		free(buff);
		return (-1);
	}
	if (!(*buff))
	{
		free(buff);
		return (-1);
	}
	if (!(*line = ft_strdup_gnl(buff)))
	{
		free(buff);
		return (-1);
	}
	return (1);
}
