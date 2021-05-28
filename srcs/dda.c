/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:28 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/28 09:21:38 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		set_default_var(t_info *info, t_var *var)
{
	var->camera_x = 2 * var->x / (double)info->scrn_w - 1;
	var->raydir_x = info->c.dir_x + info->c.plane_x * var->camera_x;
	var->raydir_y = info->c.dir_y + info->c.plane_y * var->camera_x;
	var->map_x = (int)info->c.pos_x;
	var->map_y = (int)info->c.pos_y;
	var->deltadist_x = fabs(1 / var->raydir_x);
	var->deltadist_y = fabs(1 / var->raydir_y);
	var->hit = 0;
}

static	void	stepx_sidedist_by_raydir(t_character c, t_var *var)
{
	if (var->raydir_x < 0)
	{
		var->step_x = -1;
		var->sidedist_x = (c.pos_x - var->map_x) * var->deltadist_x;
	}
	else
	{
		var->step_x = 1;
		var->sidedist_x = (var->map_x + 1 - c.pos_x) * var->deltadist_x;
	}
	if (var->raydir_y < 0)
	{
		var->step_y = -1;
		var->sidedist_y = (c.pos_y - var->map_y) * var->deltadist_y;
	}
	else
	{
		var->step_y = 1;
		var->sidedist_y = (var->map_y + 1 - c.pos_y) * var->deltadist_y;
	}
}

static void		set_side_merge_sidedist_deltadist(t_var *var)
{
	if (var->sidedist_x < var->sidedist_y)
	{
		var->sidedist_x += var->deltadist_x;
		var->map_x += var->step_x;
		var->side = 0;
	}
	else
	{
		var->sidedist_y += var->deltadist_y;
		var->map_y += var->step_y;
		var->side = 1;
	}
}

static void		stopper(t_info *info, t_var var)
{
	if (info->c.dir_x == 0 || info->c.dir_y == 0)
	{
		if (var.perpwalldist < 0.1 && info->k.s == 0)
			info->c.movspd *= var.perpwalldist;
		else
			info->c.movspd = 0.05;
	}
	else
		info->c.movspd = 0.05;
}

int				dda(t_info *info)
{
	t_var	var;

	var.x = 0;
	while (var.x < info->scrn_w)
	{
		set_default_var(info, &var);
		stepx_sidedist_by_raydir(info->c, &var);
		while (var.hit == 0)
		{
			set_side_merge_sidedist_deltadist(&var);
			if (info->map[var.map_y][var.map_x] == '1')
				var.hit = 1;
		}
		calc_perpwalldist_by_side_pos(info->c, &var);
		stopper(info, var);
		info->z[var.x] = var.perpwalldist;
		calc_d_start_d_end_by_perpwalldist(info, &var);
		set_texnum_by_side_raydir(&var);
		calc_texx_by_side_raydir(&var);
		calc_wallx_by_side(info, &var);
		draw_background(info, &var);
		draw_wall(info, &var);
		var.x++;
	}
	return (0);
}
