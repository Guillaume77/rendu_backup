/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 18:49:58 by gubourge          #+#    #+#             */
/*   Updated: 2016/10/19 16:05:03 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <errno.h>
#include "ft_ls.h"

static void	ft_search_id_value(t_list *new,
				struct passwd *usrname, struct group *grpname)
{
	if (usrname)
		new->usr_name = ft_strdup(usrname->pw_name);
	else
		new->usr_name = ft_itoa(new->stats.st_uid);
	if (grpname)
		new->grp_name = ft_strdup(grpname->gr_name);
	else
		new->grp_name = ft_itoa(new->stats.st_gid);
}

static int	ft_init_elem(t_list *new, struct dirent *entry, const char *path)
{
	if (!(new->name = ft_strdup(entry->d_name)))
		return (-1);
	if (!(new->path = ft_strdup(path)))
		return (-1);
	return (1);
}

t_list		*ft_create_elem(struct dirent *entry, const char *path)
{
	struct passwd	*usrname;
	struct group	*grpname;
	t_list			*new;

	errno = 0;
	if ((new = malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (ft_init_elem(new, entry, path) == 1)
		return (NULL);
	if (lstat(path, &(new->stats)) == -1)
		return (NULL);
	if (!(usrname = getpwuid(new->stats.st_uid)) && errno != 0)
	{
		perror("getpwuid()");
		return (NULL);
	}
	if (!(grpname = getgrgid(new->stats.st_gid)) && errno != 0)
	{
		perror("getgrgid()");
		return (NULL);
	}
	ft_search_id_value(new, usrname, grpname);
	new->next = NULL;
	return (new);
}
