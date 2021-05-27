/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 03:23:25 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/28 03:24:00 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			key_release(int key, t_info *info)
{
	if (key == KEY_W)
		info->k.w = 0;
	if (key == KEY_S)
		info->k.s = 0;
	if (key == KEY_A)
		info->k.a = 0;
	if (key == KEY_D)
		info->k.d = 0;
	if (key == KEY_LEFT)
		info->k.left = 0;
	if (key == KEY_RIGHT)
		info->k.right = 0;
	return (0);
}

int			key_press(int key, t_info *info)
{
	if (key == KEY_W)
		info->k.w = 1;
	if (key == KEY_S)
		info->k.s = 1;
	if (key == KEY_A)
		info->k.a = 1;
	if (key == KEY_D)
		info->k.d = 1;
	if (key == KEY_LEFT)
		info->k.left = 1;
	if (key == KEY_RIGHT)
		info->k.right = 1;
	if (key == KEY_ESC)
		info->k.esc = 1;
	return (0);
}
