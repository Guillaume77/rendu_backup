/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:39:26 by gubourge          #+#    #+#             */
/*   Updated: 2016/05/24 15:10:03 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"

char	*my_realloc(char *ptr, size_t size)
{
	char	*temp;
	int		i;

	ptr[size - BUFF_SIZE - 1] = 0;
	temp = ptr;
	if (!(ptr = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	i = 0;
	while (temp[i])
	{
		ptr[i] = temp[i];
		i++;
	}
	free(temp);
	return (ptr);
}


int		lencheck(int *len, char *buff, int *i)
{
	if (*len == 0)
	{
		ft_bzero(buff, ft_strlen(buff));
		*i = 0;
		return (1);
	}
	if (*len == -1)
	{
		ft_bzero(buff, ft_strlen(buff));
		*i = 0;
		*len = 0;
		return (-1);
	}
	return (*len);
}


size_t		ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

void		ft_bzero(void *s, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		++i;
	}
}

int		do_the_read(const int fd, char *buff, char *line, int *i)
{
	*i = 0;
	ft_bzero(buff, ft_strlen(buff));
	if (line)
		*line = 0;
	return (read(fd, buff, BUFF_SIZE));
}

int		get_next_line(const int fd, char **line)
{
	static char	buff[BUFF_SIZE + 1];
	static int	len = 0;
	static int	i = 0;
	int			j;

	j = 0;
	if (!line || fd < 0 || fd > 256 || BUFF_SIZE < 1)
		return (-1);
	if (len == 0)
		if ((len = do_the_read(fd, buff, NULL, &i)) <= 0)
		{
			*line = NULL;
			return (len);
		}
	if ((*line = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))) == NULL)
		return (-1);
	while (buff[i] != '\n' && buff[i])
	{
		(*line)[j++] = buff[i++];
		if (--len == 0)
			if ((len = do_the_read(fd, buff, &(*line)[j], &i)) <= 0)
				return (lencheck(&len, buff, &i));
		if (j % (BUFF_SIZE) == 0)
			if (!(*line = my_realloc(*line, j + BUFF_SIZE + 1)))
				return (-1);
	}
	len--;
	i++;
	(*line)[j] = 0;
	return (1);
}
