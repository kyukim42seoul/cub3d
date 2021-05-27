/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:57 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/27 21:18:43 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	calc_inverse_matrix(t_hub *info, t_draw_element *el)
{
	el->invdet = 1.0 / (info->c.planeX * info->c.dirY\
	- info->c.dirX * info->c.planeY);
	el->trans_x = el->invdet\
	* (info->c.dirY * el->sprt_x - info->c.dirX * el->sprt_y);
	el->trans_Y = el->invdet\
	* (-info->c.planeY * el->sprt_x + info->c.planeX * el->sprt_y);
	el->scr_x = (int)((info->g->x_render_size / 2)\
	* (1 + el->trans_x / el->trans_Y));
}

static void	set_elements(t_hub *info, t_sprite_list *start, t_draw_element *el)
{
	el->sprt_x = start->x - info->c.posX;
	el->sprt_y = start->y - info->c.posY;
	calc_inverse_matrix(info, el);
	el->sprt_h = abs((int)(info->g->y_render_size / el->trans_Y));
	el->start_y = -el->sprt_h / 2 + info->g->y_render_size / 2;
	if (el->start_y < 0)
		el->start_y = 0;
	el->end_y = el->sprt_h / 2 + info->g->y_render_size / 2;
	if (el->end_y >= info->g->y_render_size)
		el->end_y = info->g->y_render_size - 1;
	el->sprt_width = abs((int)(info->g->y_render_size / el->trans_Y));
	el->start_x = -el->sprt_width / 2 + el->scr_x;
	if (el->start_x < 0)
		el->start_x = 0;
	el->end_x = el->sprt_width / 2 + el->scr_x;
	if (el->end_x >= info->g->x_render_size)
		el->end_x = info->g->x_render_size - 1;
	el->x = el->start_x;
}

static void	project_sprite(t_hub *info, t_draw_element *el)
{
	while (el->x < el->end_x)
	{
		el->texX = (int)(256 * (el->x - (-el->sprt_width / 2 + el->scr_x))\
		* texWidth / el->sprt_width) / 256;
		if (el->trans_Y > 0 && el->x > 0 && el->x < info->g->x_render_size\
		&& el->trans_Y < info->z[el->x])
		{
			el->y = el->start_y;
			while (el->y < el->end_y)
			{
				el->d = el->y * 256 - info->g->y_render_size * 128\
				+ el->sprt_h * 128;
				el->texY = ((el->d * texHeight) / el->sprt_h) / 256;
				el->color = info->texture[4][el->texY * texWidth + el->texX];
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
		node->distance = (c.posX - node->x) * (c.posX - node->x)\
		+ (c.posY - node->y) * (c.posY - node->y);
		node = node->next;
	}
}

void		draw_sprite(t_hub *info)
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
