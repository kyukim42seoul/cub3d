/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_hub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 01:02:12 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/28 02:35:46 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	reset_graphic(t_graphic **g)
{
	*g = (t_graphic *)malloc(sizeof(t_graphic));
	if (!*g)
		error_function("Fail Malloc reset_graphic");
	(*g)->x_render_size = -1;
	(*g)->y_render_size = -1;
	(*g)->north = 0;
	(*g)->south = 0;
	(*g)->west = 0;
	(*g)->east = 0;
	(*g)->pathsprite = 0;
	(*g)->ceiling_color = -1;
	(*g)->floor_color = -1;
}

static void	reset_character(t_character *c)
{
	c->pos_x = 0;
	c->pos_y = 0;
	c->dir_x = 0;
	c->dir_y = 0;
	c->plane_x = 0;
	c->plane_y = 0;
	c->movspd = 0.05;
	c->rotspd = 0.05;
}

static void	reset_sysinfo(t_info *info)
{
	info->img.img = 0;
	info->img.addr = 0;
	info->img.bits_per_pixel = 0;
	info->img.size_line = 0;
	info->img.endian = 0;
	info->img.img_height = 0;
	info->img.img_width = 0;
	info->k.w = 0;
	info->k.s = 0;
	info->k.a = 0;
	info->k.d = 0;
	info->k.left = 0;
	info->k.right = 0;
	info->mlx = 0;
	info->win = 0;
	info->scrn_w = 0;
	info->scrn_h = 0;
	info->save = 0;
	info->fd = 0;
}

static void	reset_mapinfo(t_info *info)
{
	info->map = 0;
	info->map_width = 0;
	info->map_height = 0;
	info->number_of_sprite = 0;
	info->sprite_list = NULL;
}

void		reset_info(t_info *info)
{
	reset_sysinfo(info);
	reset_graphic(&info->g);
	reset_character(&info->c);
	reset_mapinfo(info);
}
