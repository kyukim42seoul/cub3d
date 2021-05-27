/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:32 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/28 01:15:36 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_image(t_info *info)
{
	int	y;
	int	x;

	y = 0;
	while (y < info->scrn_h)
	{
		x = 0;
		while (x < info->scrn_w)
		{
			info->img.addr[y * info->img.size_line / 4 + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	if (info->save == 0)
		mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	draw_background(t_info *info, t_var *var)
{
	int	eyesight;
	int	y;

	eyesight = info->scrn_h / 2;
	y = 0;
	while (y < eyesight)
	{
		info->buf[y][var->x] = info->g->ceiling_color;
		y++;
	}
	while (y < info->scrn_h)
	{
		info->buf[y][var->x] = info->g->floor_color;
		y++;
	}
}

void	draw_wall(t_info *info, t_var *var)
{
	var->y = var->drawstart;
	if (var->drawstart < 0)
		var->y = 0;
	while (var->y < var->drawend)
	{
		var->tex_y = (double)(var->y - var->drawstart) / var->line_h * 63;
		var->color = info->texture[var->texnum]\
		[TEXWIDTH * var->tex_y + var->tex_x];
		if (var->side == 1)
			var->color = (var->color >> 1) & 8355711;
		info->buf[var->y][var->x] = var->color;
		var->y++;
	}
}
