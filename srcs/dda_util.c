/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 15:16:20 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/28 01:15:29 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_perpwalldist_by_side_pos(t_character c, t_var *var)
{
	if (var->side == 0)
		var->perpwalldist = (var->map_x - c.pos_x + (1 - var->step_x) / 2)\
		/ var->raydir_x;
	else
		var->perpwalldist = (var->map_y - c.pos_y + (1 - var->step_y) / 2)\
		/ var->raydir_y;
}

void	calc_d_start_d_end_by_perpwalldist(t_info *info, t_var *var)
{
	var->line_h = (int)(info->scrn_h / var->perpwalldist);
	var->drawstart = (info->scrn_h / 2) - (var->line_h / 2);
	var->drawend = (var->line_h / 2) + (info->scrn_h / 2);
	if (var->drawend >= info->scrn_h)
		var->drawend = info->scrn_h;
}

void	set_texnum_by_side_raydir(t_var *var)
{
	if (var->side == 0 && var->raydir_x > 0)
		var->texnum = 3;
	else if (var->side == 0 && var->raydir_x < 0)
		var->texnum = 2;
	else if (var->side == 1 && var->raydir_y > 0)
		var->texnum = 1;
	else if (var->side == 1 && var->raydir_y < 0)
		var->texnum = 0;
}

void	calc_texx_by_side_raydir(t_var *var)
{
	var->tex_x = (int)(var->wall_x * (double)TEXWIDTH);
	if (var->side == 0 && var->raydir_x < 0)
		var->tex_x = TEXWIDTH - var->tex_x - 1;
	if (var->side == 1 && var->raydir_y > 0)
		var->tex_x = TEXWIDTH - var->tex_x - 1;
}

void	calc_wallx_by_side(t_info *info, t_var *var)
{
	if (var->side == 0)
		var->wall_x = info->c.pos_y + var->perpwalldist * var->raydir_y;
	else
		var->wall_x = info->c.pos_x + var->perpwalldist * var->raydir_x;
	var->wall_x -= floor(var->wall_x);
}
