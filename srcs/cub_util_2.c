/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_util_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 20:38:45 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/27 22:35:07 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_image(t_hub *info, int *texture, char *path, t_image *img)
{
	int	x;
	int	y;

	y = 0;
	img->img = mlx_xpm_file_to_image(info->mlx, path,\
	&img->img_width, &img->img_height);
	if (!img->img)
		error_function("Invaild Path");
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,\
	&img->size_line, &img->endian);
	while (y < info->img.img_height)
	{
		x = 0;
		while (x < info->img.img_width)
		{
			texture[y * info->img.img_width + x] =\
			info->img.addr[y * info->img.img_width + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, info->img.img);
}

void	load_texture(t_hub *info)
{
	load_image(info, info->texture[0], info->g->north, &info->img);
	load_image(info, info->texture[1], info->g->south, &info->img);
	load_image(info, info->texture[2], info->g->west, &info->img);
	load_image(info, info->texture[3], info->g->east, &info->img);
	load_image(info, info->texture[4], info->g->pathsprite, &info->img);
}

void	set_texture_buf(t_hub *info)
{
	int	num;
	int	tex_h;
	int	tex_w;

	num = 0;
	tex_h = texHeight;
	tex_w = texWidth;
	info->texture = (int **)malloc(sizeof(int *) * 5);
	if (!info->texture)
		error_function("Fail Malloc set_texture_buf");
	while (num < 5)
	{
		info->texture[num] = (int *)malloc(sizeof(int) * tex_h * tex_w);
		if (!info->texture[num])
			error_function("Fail Malloc set_texture_buf");
		num++;
	}
}

void	set_screen_buf(t_hub *info)
{
	int	y;

	y = 0;
	info->buf = (int **)malloc(sizeof(int *) * info->scrn_h);
	if (!info->buf)
		error_function("Fail Malloc set_screen_buf");
	while (y < info->scrn_h)
	{
		info->buf[y] = (int *)malloc(sizeof(int) * info->scrn_w);
		if (!info->buf[y])
			error_function("Fail Malloc set_screen_buf");
		y++;
	}
}

void	check_render_size(t_hub *info)
{
	mlx_get_screen_size(info->mlx, &info->scrn_w, &info->scrn_h);
	if (info->g->x_render_size == 0 || info->g->y_render_size == 0)
		error_function("Invaild Rendersize");
	if (info->g->x_render_size > info->scrn_w)
		info->g->x_render_size = info->scrn_w;
	if (info->g->y_render_size > info->scrn_h)
		info->g->y_render_size = info->scrn_h;
	info->scrn_w = info->g->x_render_size;
	info->scrn_h = info->g->y_render_size;
}
