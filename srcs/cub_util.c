#include "cub3D.h"

void	error_function(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	exit(0);
}

void	combine_color(int *color, int red, int green, int blue)
{
	int	temp;

	temp = 0;
	temp |= red << 16;
	temp |= green << 8;
	temp |= blue;
	*color = temp;
}

void	load_image(t_hub *info, int *texture, char *path, t_image *img)
{
	int	x;
	int	y;

	y = 0;
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->size_line, &img->endian);
	while (y < info->img.img_height)
	{
		x = 0;
		while (x < info->img.img_width)
		{
			texture[y * info->img.img_width + x] = info->img.addr[y * info->img.img_width + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, info->img.img);
}

void	load_texture(t_hub *info)
{
	load_image(info, info->texture[0], info->g->path_to_the_north_texture, &info->img);
	load_image(info, info->texture[1], info->g->path_to_the_south_texture, &info->img);
	load_image(info, info->texture[2], info->g->path_to_the_west_texture, &info->img);
	load_image(info, info->texture[3], info->g->path_to_the_east_texture, &info->img);
	load_image(info, info->texture[4], info->g->path_to_the_sprite_texture, &info->img);
}

void	set_texture_buf(t_hub *info)
{
	int	temp;

	temp = 0;
	info->texture = (int **)malloc(sizeof(int *) * 5); // texNum 으로 나중에 교체
	while (temp < 5)
	{
		info->texture[temp] = (int *)malloc(sizeof(int) * texHeight * texWidth);
		temp++;
	}
}

void	set_screen_buf(t_hub *info)
{
	int	temp;

	temp = 0;
	info->buf = (int **)malloc(sizeof(int *) * info->screenheight);
	while (temp < info->screenheight)
	{
		info->buf[temp] = (int *)malloc(sizeof(int) * info->screenwidth);
		temp++;
	}
}

void	free_texture_buf(t_hub *info)
{
	int	temp;

	temp = 0;
	while (temp < info->screenheight)
	{
		free(info->texture[temp]);
		temp++;
	}
	free(info->texture[temp]);
	free(info->texture);
}

void	set_pixel_color(t_image img, int x, int y, int color)
{
	char	*dst;

	dst = (char *)(img.addr + (y * img.size_line + x * (img.bits_per_pixel / 8)));

	*(unsigned int *)dst = color;
}
