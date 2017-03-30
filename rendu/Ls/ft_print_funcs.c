/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 14:37:47 by gubourge          #+#    #+#             */
/*   Updated: 2016/10/19 15:52:31 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ft_ls.h"

int		print_date(struct stat stats)
{
	int				i;
	int				length;
	char			*str;
	unsigned int	time_a;
	unsigned int	time_b;

	if (!(str = ctime(&stats.st_mtime)))
		return (-1);
	time_a = time(NULL);
	time_b = stats.st_mtime;
	i = 3;
	length = 16;
	while (i < length)
	{
		if (i == 11 && ((time_a - SIX_M > time_b) || (time_a + SIX_M < time_b)))
		{
			i += 8;
			length += 8;
		}
		write(1, &str[i], 1);
		++i;
	}
	return (0);
}

void	print_mode(int perm)
{
	if (S_ISREG(perm))
		write(1, "-", 1);
	else if (S_ISDIR(perm))
		write(1, "d", 1);
	else if (S_ISCHR(perm))
		write(1, "c", 1);
	else if (S_ISBLK(perm))
		write(1, "b", 1);
	else if (S_ISFIFO(perm))
		write(1, "p", 1);
	else if (S_ISLNK(perm))
		write(1, "l", 1);
	else if (S_ISSOCK(perm))
		write(1, "s", 1);
}

void	print_perms_bis(int perm)
{
	perm & S_IROTH ? write(1, "r", 1) : write(1, "-", 1);
	perm & S_IWOTH ? write(1, "w", 1) : write(1, "-", 1);
	if ((perm & S_ISVTX) && (perm & S_IXOTH))
		write(1, "t", 1);
	else if ((perm & S_ISVTX) && !(perm & S_IXOTH))
		write(1, "T", 1);
	else if (!(perm & S_ISVTX) && (perm & S_IXOTH))
		write(1, "x", 1);
	else
		write(1, "-", 1);
}

void	print_perms(int perm)
{
	perm & S_IRUSR ? write(1, "r", 1) : write(1, "-", 1);
	perm & S_IWUSR ? write(1, "w", 1) : write(1, "-", 1);
	if ((perm & S_ISUID) && (perm & S_IXUSR))
		write(1, "s", 1);
	else if ((perm & S_ISUID) && !(perm & S_IXUSR))
		write(1, "S", 1);
	else if (!(perm & S_ISUID) && (perm & S_IXUSR))
		write(1, "x", 1);
	else
		write(1, "-", 1);
	perm & S_IRGRP ? write(1, "r", 1) : write(1, "-", 1);
	perm & S_IWGRP ? write(1, "w", 1) : write(1, "-", 1);
	if ((perm & S_ISGID) && (perm & S_IXGRP))
		write(1, "s", 1);
	else if ((perm & S_ISGID) && !(perm & S_IXGRP))
		write(1, "S", 1);
	else if (!(perm & S_ISGID) && (perm & S_IXGRP))
		write(1, "x", 1);
	else
		write(1, "-", 1);
	print_perms_bis(perm);
}

void	print_padd(int padd, int size)
{
	while (padd-- > size)
		write(1, " ", 1);
}
