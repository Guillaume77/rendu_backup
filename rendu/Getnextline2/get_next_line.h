/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:38:31 by gubourge          #+#    #+#             */
/*   Updated: 2016/06/29 14:13:58 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 4096
# define MAX_FD 256

# include <string.h>
# include "libft/libft.h"

typedef struct	s_fd
{
	char		*buff;
	int			fd;
	struct s_fd	*next;
}				t_fd;

int				get_next_line(const int fd, char **line);
size_t			ft_strlen(const char *s);
char			*ft_strdup(char *src);
char			*ft_strjoin(char const *s1, char const *s2);
void			*ft_memalloc(size_t size);

#endif
