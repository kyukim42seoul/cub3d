/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:37 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/31 13:11:17 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_ws(t_info *info)
{
	if (info->k.w == 1)
	{
		if (info->map[(int)info->c.pos_y]\
		[(int)(info->c.pos_x + info->c.dir_x * info->c.movspd)] == '0')
			info->c.pos_x += info->c.dir_x * info->c.movspd;
		if (info->map[(int)(info->c.pos_y + info->c.dir_y * info->c.movspd)]\
		[(int)info->c.pos_x] == '0')
			info->c.pos_y += info->c.dir_y * info->c.movspd;
	}
	if (info->k.s == 1)
	{
		if (info->map[(int)info->c.pos_y]\
		[(int)(info->c.pos_x - info->c.dir_x * info->c.movspd)] == '0')
			info->c.pos_x -= info->c.dir_x * info->c.movspd;
		if (info->map[(int)(info->c.pos_y - info->c.dir_y * info->c.movspd)]\
		[(int)info->c.pos_x] == '0')
			info->c.pos_y -= info->c.dir_y * info->c.movspd;
	}
}

static void	update_ad(t_info *info)
{
	if (info->k.a == 1)
	{
		if (info->map[(int)info->c.pos_y]\
		[(int)(info->c.pos_x + info->c.dir_y * info->c.movspd)] == '0')
			info->c.pos_x += info->c.dir_y * info->c.movspd;
		if (info->map[(int)(info->c.pos_y - info->c.dir_x * info->c.movspd)]\
		[(int)info->c.pos_x] == '0')
			info->c.pos_y -= info->c.dir_x * info->c.movspd;
	}
	if (info->k.d == 1)
	{
		if (info->map[(int)info->c.pos_y]\
		[(int)(info->c.pos_x - info->c.dir_y * info->c.movspd)] == '0')
			info->c.pos_x -= info->c.dir_y * info->c.movspd;
		if (info->map[(int)(info->c.pos_y + info->c.dir_x * info->c.movspd)]\
		[(int)info->c.pos_x] == '0')
			info->c.pos_y += info->c.dir_x * info->c.movspd;
	}
}

static void	update_arrow(t_info *info, double olddir_x, double oldplane_x)
{
	if (info->k.left == 1 && info->k.right != 1)
	{
		info->c.dir_x = info->c.dir_x * cos(-info->c.rotspd)\
		- info->c.dir_y * sin(-info->c.rotspd);
		info->c.dir_y = olddir_x * sin(-info->c.rotspd)\
		+ info->c.dir_y * cos(-info->c.rotspd);
		info->c.plane_x = info->c.plane_x * cos(-info->c.rotspd)\
		- info->c.plane_y * sin(-info->c.rotspd);
		info->c.plane_y = oldplane_x * sin(-info->c.rotspd)\
		+ info->c.plane_y * cos(-info->c.rotspd);
	}
	if (info->k.right == 1 && info->k.left != 1)
	{
		info->c.dir_x = info->c.dir_x * cos(info->c.rotspd)\
		- info->c.dir_y * sin(info->c.rotspd);
		info->c.dir_y = olddir_x * sin(info->c.rotspd)\
		+ info->c.dir_y * cos(info->c.rotspd);
		info->c.plane_x = info->c.plane_x * cos(info->c.rotspd)\
		- info->c.plane_y * sin(info->c.rotspd);
		info->c.plane_y = oldplane_x * sin(info->c.rotspd)\
		+ info->c.plane_y * cos(info->c.rotspd);
	}
}

int			key_update(t_info *info)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = 0;
	oldplane_x = 0;
	if ((info->k.a == 1) || info->k.d == 1)
	{
		olddir_x = info->c.dir_x;
		oldplane_x = info->c.plane_x;
	}
	if (info->k.esc == 1)
		exit(0);
	update_ws(info);
	update_ad(info);
	update_arrow(info, olddir_x, oldplane_x);
	return (0);
}
