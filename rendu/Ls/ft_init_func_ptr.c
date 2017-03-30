/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_func_ptr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 14:34:52 by gubourge          #+#    #+#             */
/*   Updated: 2016/10/19 14:45:25 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_func_ptr(func_ptr *func_strcmp)
{
	func_strcmp[S_r + S_t] = &ft_strcmp_rt;
	func_strcmp[S_r + S_t + S_l] = &ft_strcmp_rt;
	func_strcmp[S_r + S_t + S_R] = &ft_strcmp_rt;
	func_strcmp[S_r + S_t + S_R + S_l] = &ft_strcmp_rt;
	func_strcmp[S_r] = &ft_strcmp_r;
	func_strcmp[S_r + S_l] = &ft_strcmp_r;
	func_strcmp[S_r + S_R] = &ft_strcmp_r;
	func_strcmp[S_r + S_l + S_R] = &ft_strcmp_r;
	func_strcmp[S_t] = &ft_strcmp_t;
	func_strcmp[S_t + S_l] = &ft_strcmp_t;
	func_strcmp[S_t + S_R] = &ft_strcmp_t;
	func_strcmp[S_t + S_R + S_l] = &ft_strcmp_t;
	func_strcmp[0] = &ft_strcmp_modify;
	func_strcmp[S_l] = &ft_strcmp_modify;
	func_strcmp[S_R] = &ft_strcmp_modify;
	func_strcmp[S_R + S_l] = &ft_strcmp_modify;
	func_strcmp[S_t + S_l] = &ft_strcmp_modify;
}
