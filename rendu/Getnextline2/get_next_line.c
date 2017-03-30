/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:39:26 by gubourge          #+#    #+#             */
/*   Updated: 2016/06/30 19:00:47 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static t_fd			*ft_get_good_list(t_fd **list, int fd)
{
	t_fd	*cpy;

	if (!*list)
	{
		if (!(*list = (t_fd*)ft_memalloc(sizeof(t_fd))))
			return (NULL);
		(*list)->fd = fd;
		return (*list);
	}
	cpy = *list;
	while (cpy->fd != fd)
	{
		if (!cpy->next)
		{
			if (!(cpy->next = (t_fd*)ft_memalloc(sizeof(t_fd))))
				return (NULL);
			cpy->next->fd = fd;
			return (cpy->next);
		}
		cpy = cpy->next;
	}
	return (cpy);
}

static char			*ft_strdup_gnl(char **buff)
{
	char	*dest;
	char	*tmp;
	int		i;

	i = 0;
	while ((*buff)[i] != '\n' && (*buff)[i])
		++i;
	if (!(dest = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while ((*buff)[i] != '\n' && (*buff)[i])
	{
		dest[i] = (*buff)[i];
		++i;
	}
	dest[i] = 0;
	if ((*buff)[i] == '\n')
		++i;
	tmp = ft_strdup(&(*buff)[i]);
	free(*buff);
	*buff = tmp;
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
	}
	if (ret == -1)
	{
		free(*buff);
		*buff = NULL;
	}
	return (ret);
}

static void			free_current(t_fd **buff, int fd)
{
	t_fd	*list;
	t_fd	*prev;

	list = *buff;
	if (list->fd == fd)
	{
		*buff = list->next;
		free(list);
	}
	else
	{
		while (list->fd != fd)
		{
			prev = list;
			list = list->next;
		}
		prev->next = list->next;
		free(list);
	}
}

int					get_next_line(const int fd, char **line)
{
	static t_fd	*buff = NULL;
	t_fd		*current;

	if (!line || fd < 0)
		return (-1);
	if (!(current = ft_get_good_list(&buff, fd)))
		return (-1);
	if (!current->buff)
		if (do_the_read(current->fd, &(current->buff)) == -1)
		{
			free_current(&buff, current->fd);
			return (-1);
		}
	if (!*(current->buff))
	{
		free_current(&buff, current->fd);
		return (0);
	}
	if (!(*line = ft_strdup_gnl(&(current->buff))))
	{
		free_current(&buff, current->fd);
		return (-1);
	}
	return (1);
}
