/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:18 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/28 02:04:18 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	bmp_file_header(t_info *info, unsigned char *header)
{
	int	temp;

	temp = 54 + info->scrn_h * info->scrn_w * 4;
	header[0] = 'B';
	header[1] = 'M';
	header[2] = (unsigned char)temp;
	header[3] = (unsigned char)(temp >> 8);
	header[4] = (unsigned char)(temp >> 16);
	header[5] = (unsigned char)(temp >> 24);
	header[10] = 54;
}

static	void	bmp_info_header(t_info *info, unsigned char *header)
{
	int	temp;

	temp = info->scrn_h;
	header[14] = 40;
	header[18] = (unsigned char)(info->scrn_w);
	header[19] = (unsigned char)(info->scrn_w >> 8);
	header[20] = (unsigned char)(info->scrn_w >> 16);
	header[21] = (unsigned char)(info->scrn_w >> 24);
	header[22] = (unsigned char)(temp);
	header[23] = (unsigned char)(temp >> 8);
	header[24] = (unsigned char)(temp >> 16);
	header[25] = (unsigned char)(temp >> 24);
	header[26] = 1;
	header[28] = 32;
}

static	void	put_bmp_data(t_info *info, unsigned char *header)
{
	int	fd;
	int	y;

	fd = 0;
	y = 0;
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (fd < 0)
		error_function("Fail Open create .bpm");
	write(fd, header, 54);
	info->img.addr = info->img.addr + info->scrn_h * info->img.size_line / 4;
	while (y < info->scrn_h)
	{
		info->img.addr -= info->img.size_line / 4;
		write(fd, info->img.addr, (info->scrn_w * 4));
		y++;
	}
}

void			make_bitmap(char **argv, t_info *info)
{
	unsigned char	header[54];

	ft_bzero(header, 54);
	info->fd = open(argv[1], O_RDONLY);
	if (info->fd < 0)
		error_function("Fail Open .cub");
	start_parsing(info->fd, &info->map, info);
	info->mlx = mlx_init();
	check_render_size(info);
	info->z = (double *)malloc(sizeof(double) * info->g->x_render_size);
	set_texture_buf(info);
	set_screen_buf(info);
	load_texture(info);
	info->img.img = mlx_new_image(info->mlx, info->scrn_w, info->scrn_h);
	info->img.addr = (int *)mlx_get_data_addr(info->img.img,\
	&info->img.bits_per_pixel, &info->img.size_line, &info->img.endian);
	dda(info);
	set_sprite_distance(info->c, info->sprite_list->next);
	sort_sprite_node(info->sprite_list->next);
	draw_sprite(info);
	draw_image(info);
	bmp_file_header(info, header);
	bmp_info_header(info, header);
	put_bmp_data(info, header);
}
