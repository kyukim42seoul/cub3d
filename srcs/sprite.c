/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:57 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/28 01:16:31 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_inverse_matrix(t_info *info, t_draw_element *el)
{
	el->invdet = 1.0 / (info->c.plane_x * info->c.dir_y\
	- info->c.dir_x * info->c.plane_y);
	el->trans_x = el->invdet\
	* (info->c.dir_y * el->sprt_x - info->c.dir_x * el->sprt_y);
	el->trans_y = el->invdet\
	* (-info->c.plane_y * el->sprt_x + info->c.plane_x * el->sprt_y);
	el->scr_x = (int)((info->g->x_render_size / 2)\
	* (1 + el->trans_x / el->trans_y));
}

static void	set_elements(t_info *info, t_sprite_list *start, t_draw_element *el)
{
	el->sprt_x = start->x - info->c.pos_x;
	el->sprt_y = start->y - info->c.pos_y;
	calc_inverse_matrix(info, el);
	el->sprt_h = abs((int)(info->g->y_render_size / el->trans_y));
	el->start_y = -el->sprt_h / 2 + info->g->y_render_size / 2;
	if (el->start_y < 0)
		el->start_y = 0;
	el->end_y = el->sprt_h / 2 + info->g->y_render_size / 2;
	if (el->end_y >= info->g->y_render_size)
		el->end_y = info->g->y_render_size - 1;
	el->sprt_width = abs((int)(info->g->y_render_size / el->trans_y));
	el->start_x = -el->sprt_width / 2 + el->scr_x;
	if (el->start_x < 0)
		el->start_x = 0;
	el->end_x = el->sprt_width / 2 + el->scr_x;
	if (el->end_x >= info->g->x_render_size)
		el->end_x = info->g->x_render_size - 1;
	el->x = el->start_x;
}

static void	project_sprite(t_info *info, t_draw_element *el)
{
	while (el->x < el->end_x)
	{
		el->tex_x = (int)(256 * (el->x - (-el->sprt_width / 2 + el->scr_x))\
		* TEXWIDTH / el->sprt_width) / 256;
		if (el->trans_y > 0 && el->x > 0 && el->x < info->g->x_render_size\
		&& el->trans_y < info->z[el->x])
		{
			el->y = el->start_y;
			while (el->y < el->end_y)
			{
				el->d = el->y * 256 - info->g->y_render_size * 128\
				+ el->sprt_h * 128;
				el->tex_y = ((el->d * TEXHEIGHT) / el->sprt_h) / 256;
				el->color = info->texture[4][el->tex_y * TEXWIDTH + el->tex_x];
				if ((el->color & 0x00FFFFFF) != 0)
					info->buf[el->y][el->x] = el->color;
				el->y++;
			}
		}
		el->x++;
	}
}

void		set_sprite_distance(t_character c, t_sprite_list *node)
{
	while (node)
	{
		node->distance = (c.pos_x - node->x) * (c.pos_x - node->x)\
		+ (c.pos_y - node->y) * (c.pos_y - node->y);
		node = node->next;
	}
}

void		draw_sprite(t_info *info)
{
	t_draw_element	el;
	t_sprite_list	*start;

	start = info->sprite_list->next;
	while (start)
	{
		set_elements(info, start, &el);
		project_sprite(info, &el);
		start = start->next;
	}
}
