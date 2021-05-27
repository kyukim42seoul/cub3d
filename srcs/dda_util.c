/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 15:16:20 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/27 21:20:29 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calc_perpwalldist_by_side_pos(t_character c, t_var *var)
{
	if (var->side == 0)
		var->perpWallDist = (var->mapX - c.posX + (1 - var->stepX) / 2)\
		/ var->rayDirX;
	else
		var->perpWallDist = (var->mapY - c.posY + (1 - var->stepY) / 2)\
		/ var->rayDirY;
}

void	calc_drawstart_drawend_by_perpwalldist(t_hub *info, t_var *var)
{
	var->lineHeight = (int)(info->scrn_h / var->perpWallDist);
	var->drawStart = (info->scrn_h / 2) - (var->lineHeight / 2);
	var->drawEnd = (var->lineHeight / 2) + (info->scrn_h / 2);
	if (var->drawEnd >= info->scrn_h)
		var->drawEnd = info->scrn_h;
}

void	set_texnum_by_side_raydir(t_var *var)
{
	if (var->side == 0 && var->rayDirX > 0)
		var->texNum = 3;
	else if (var->side == 0 && var->rayDirX < 0)
		var->texNum = 2;
	else if (var->side == 1 && var->rayDirY > 0)
		var->texNum = 1;
	else if (var->side == 1 && var->rayDirY < 0)
		var->texNum = 0;
}

void	calc_texx_by_side_raydir(t_var *var)
{
	var->texX = (int)(var->wallX * (double)texWidth);
	if (var->side == 0 && var->rayDirX < 0)
		var->texX = texWidth - var->texX - 1;
	if (var->side == 1 && var->rayDirY > 0)
		var->texX = texWidth - var->texX - 1;
}

void	calc_wallx_by_side(t_hub *info, t_var *var)
{
	if (var->side == 0)
		var->wallX = info->c.posY + var->perpWallDist * var->rayDirY;
	else
		var->wallX = info->c.posX + var->perpWallDist * var->rayDirX;
	var->wallX -= floor(var->wallX);
}
