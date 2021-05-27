/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:28 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/27 21:15:26 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void		set_default_var(t_hub *info, t_var *var)
{
	var->cameraX = 2 * var->x / (double)info->scrn_w - 1;
	var->rayDirX = info->c.dirX + info->c.planeX * var->cameraX;
	var->rayDirY = info->c.dirY + info->c.planeY * var->cameraX;
	var->mapX = (int)info->c.posX;
	var->mapY = (int)info->c.posY;
	var->deltaDistX = fabs(1 / var->rayDirX);
	var->deltaDistY = fabs(1 / var->rayDirY);
	var->hit = 0;
}

static	void	stepx_sidedist_by_raydir(t_character c, t_var *var)
{
	if (var->rayDirX < 0)
	{
		var->stepX = -1;
		var->sideDistX = (c.posX - var->mapX) * var->deltaDistX;
	}
	else
	{
		var->stepX = 1;
		var->sideDistX = (var->mapX + 1 - c.posX) * var->deltaDistX;
	}
	if (var->rayDirY < 0)
	{
		var->stepY = -1;
		var->sideDistY = (c.posY - var->mapY) * var->deltaDistY;
	}
	else
	{
		var->stepY = 1;
		var->sideDistY = (var->mapY + 1 - c.posY) * var->deltaDistY;
	}
}

static void		set_side_merge_sidedist_deltadist(t_var *var)
{
	if (var->sideDistX < var->sideDistY)
	{
		var->sideDistX += var->deltaDistX;
		var->mapX += var->stepX;
		var->side = 0;
	}
	else
	{
		var->sideDistY += var->deltaDistY;
		var->mapY += var->stepY;
		var->side = 1;
	}
}

int				dda(t_hub *info)
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
			if (info->map[var.mapY][var.mapX] == '1')
				var.hit = 1;
		}
		calc_perpwalldist_by_side_pos(info->c, &var);
		info->z[var.x] = var.perpWallDist;
		calc_drawstart_drawend_by_perpwalldist(info, &var);
		set_texnum_by_side_raydir(&var);
		calc_texx_by_side_raydir(&var);
		calc_wallx_by_side(info, &var);
		draw_background(info, &var);
		draw_wall(info, &var);
		var.x++;
	}
	return (0);
}
