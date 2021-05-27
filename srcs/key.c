/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:37 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/27 16:33:47 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	update_ws(t_hub *info)
{
	if (info->k.w == 1)
	{
		if (info->map[(int)info->c.posY]\
		[(int)(info->c.posX + info->c.dirX * info->c.movspd)] == '0')
			info->c.posX += info->c.dirX * info->c.movspd;
		if (info->map[(int)(info->c.posY + info->c.dirY * info->c.movspd)]\
		[(int)info->c.posX] == '0')
			info->c.posY += info->c.dirY * info->c.movspd;
	}
	if (info->k.s == 1)
	{
		if (info->map[(int)info->c.posY]\
		[(int)(info->c.posX - info->c.dirX * info->c.movspd)] == '0')
			info->c.posX -= info->c.dirX * info->c.movspd;
		if (info->map[(int)(info->c.posY - info->c.dirY * info->c.movspd)]\
		[(int)info->c.posX] == '0')
			info->c.posY -= info->c.dirY * info->c.movspd;
	}
}

static void	update_ad(t_hub *info, double olddirx, double oldplanex)
{
	if (info->k.a == 1)
	{
		info->c.dirX = info->c.dirX * cos(-info->c.rotspd)\
		- info->c.dirY * sin(-info->c.rotspd);
		info->c.dirY = olddirx * sin(-info->c.rotspd)\
		+ info->c.dirY * cos(-info->c.rotspd);
		info->c.planeX = info->c.planeX * cos(-info->c.rotspd)\
		- info->c.planeY * sin(-info->c.rotspd);
		info->c.planeY = oldplanex * sin(-info->c.rotspd)\
		+ info->c.planeY * cos(-info->c.rotspd);
	}
	if (info->k.d == 1)
	{
		info->c.dirX = info->c.dirX * cos(info->c.rotspd)\
		- info->c.dirY * sin(info->c.rotspd);
		info->c.dirY = olddirx * sin(info->c.rotspd)\
		+ info->c.dirY * cos(info->c.rotspd);
		info->c.planeX = info->c.planeX * cos(info->c.rotspd)\
		- info->c.planeY * sin(info->c.rotspd);
		info->c.planeY = oldplanex * sin(info->c.rotspd)\
		+ info->c.planeY * cos(info->c.rotspd);
	}
}

int			key_update(t_hub *info)
{
	double	olddirx;
	double	oldplanex;

	olddirx = 0;
	oldplanex = 0;
	if ((info->k.a == 1) || info->k.d == 1)
	{
		olddirx = info->c.dirX;
		oldplanex = info->c.planeX;
	}
	if (info->k.esc == 1)
		exit(0);
	update_ws(info);
	update_ad(info, olddirx, oldplanex);
	return (0);
}

int			key_release(int key, t_hub *info)
{
	if (key == KEY_W)
		info->k.w = 0;
	if (key == KEY_S)
		info->k.s = 0;
	if (key == KEY_A)
		info->k.a = 0;
	if (key == KEY_D)
		info->k.d = 0;
	return (0);
}

int			key_press(int key, t_hub *info)
{
	if (key == KEY_W)
		info->k.w = 1;
	if (key == KEY_S)
		info->k.s = 1;
	if (key == KEY_D)
		info->k.d = 1;
	if (key == KEY_A)
		info->k.a = 1;
	if (key == KEY_ESC)
		info->k.esc = 1;
	return (0);
}
