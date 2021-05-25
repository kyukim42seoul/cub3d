#include "cub3D.h"

static	void	bmp_file_header(t_hub *info, unsigned char *header)
{
	int	temp;

	temp = 54 + info->screenheight * info->screenwide * 4;
	header[0] = 'B';
	header[1] = 'M';
	header[2] = (unsigned char)temp;
	header[3] = (unsigned char)(temp >> 8);
	header[4] = (unsigned char)(temp >> 16);
	header[5] = (unsigned char)(temp >> 24);
	header[10] = 54;
}

static	void	bmp_info_header(t_hub *info, unsigned char *header)
{
	int	temp;

	temp = info->screenheight;
	header[14] = 40;
	header[18] = (unsigned char)(info->screenwide);
	header[19] = (unsigned char)(info->screenwide >> 8);
	header[20] = (unsigned char)(info->screenwide >> 16);
	header[21] = (unsigned char)(info->screenwide >> 24);
	header[22] = (unsigned char)(temp);
	header[23] = (unsigned char)(temp >> 8);
	header[24] = (unsigned char)(temp >> 16);
	header[25] = (unsigned char)(temp >> 24);
	header[26] = 1;
	header[28] = 32;
}

static	void	put_bmp_data(t_hub *info, unsigned char *header)
{
	int	fd;
	int	y;

	fd = 0;
	y = 0;
	fd = open("test.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0755);
	write(fd, header, 54);
	info->image.addr = info->image.addr + info->screenheight * info->image.line_length / 4;
	while (y < info->screenheight)
	{
		info->image.addr -= info->image.line_length / 4;
		write(fd, info->image.addr, (info->screenwide * 4));
		y++;
	}
}

void	make_bitmap(char **argv, t_hub *info, int fd)
{
	unsigned char	header[54];

	ft_bzero(header, 54);
	info->mlx = mlx_init();
	fd = open(argv[1], O_RDONLY);
	start_parsing(fd, &info->map, info);
	info->screenwide = info->graphic->x_render_size;
	info->screenheight = info->graphic->y_render_size;
	info->z = (double *)malloc(sizeof(double) * info->graphic->x_render_size);
	set_texture_buf(info);
	set_screen_buf(info);
	load_texture(info);
	info->win = mlx_new_window(info->mlx, info->graphic->x_render_size, info->graphic->y_render_size, "test");
	info->image.img = mlx_new_image(info->mlx, info->screenwide, info->screenheight);
	info->image.addr = (int *)mlx_get_data_addr(info->image.img, &info->image.bits_per_pixel, &info->image.line_length, &info->image.endian);
	dda(info);
	set_sprite_distance(info, info->sprite_list->next);
	sort_sprite_node(info->sprite_list->next);
	draw_sprite(info);
	draw_image(info);
	bmp_file_header(info, header);
	bmp_info_header(info, header);
	put_bmp_data(info, header);
}
