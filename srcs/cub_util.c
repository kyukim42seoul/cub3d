#include "cub3D.h"

void	combine_color(int *color, int red, int green, int blue)
{
	*color |= red << 16;
	*color |= green << 8;
	*color |= blue;
}

void	load_image(t_hub *info, int *texture, char *path, t_idata *image)
{
	int	x;
	int	y;

	y = 0;
	image->img = mlx_xpm_file_to_image(info->mlx, path, &image->img_width, &image->img_height);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length, &image->endian);
	while (y < info->image.img_height)
	{
		x = 0;
		while (x < info->image.img_width)
		{
			texture[y * info->image.img_width + x] = info->image.addr[y * info->image.img_width + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, info->image.img);
}

void	load_texture(t_hub *info)
{
	load_image(info, info->texture[0], info->graphic->path_to_the_north_texture, &info->image);
	load_image(info, info->texture[1], info->graphic->path_to_the_south_texture, &info->image);
	load_image(info, info->texture[2], info->graphic->path_to_the_west_texture, &info->image);
	load_image(info, info->texture[3], info->graphic->path_to_the_east_texture, &info->image);
	load_image(info, info->texture[4], info->graphic->path_to_the_sprite_texture, &info->image);
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
		info->buf[temp] = (int *)malloc(sizeof(int) * info->screenwide);
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

void	set_pixel_color(t_hub *info, int x, int y, int color)
{
	char	*dst;

	dst = (char *)(info->image.addr + (y * info->image.line_length + x * (info->image.bits_per_pixel / 8)));

	*(unsigned int *)dst = color;
}

void	reset_info(t_hub *info)
{
	info->error = 0;
	info->error_message = 0;
	info->graphic->x_render_size = 0;
	info->graphic->y_render_size = 0;
	info->graphic->f_red = -1;
	info->graphic->f_green = -1;
	info->graphic->f_blue = -1;
	info->graphic->c_red = -1;
	info->graphic->c_green = -1;
	info->graphic->c_blue = -1;
	info->graphic->path_to_the_north_texture = 0;
	info->graphic->path_to_the_south_texture = 0;
	info->graphic->path_to_the_west_texture = 0;
	info->graphic->path_to_the_east_texture = 0;
	info->graphic->path_to_the_sprite_texture = 0;
	info->moveSpeed = 0.05;
	info->rotationSpeed = 0.05;
	info->posX = 0;
	info->posY = 0;
	info->dirX = 0;
	info->dirY = 0;
	info->planeX = 0;
	info->planeY = 0;
	info->mlx = 0;
	info->win = 0;
	info->image.img = 0;
	info->screenwide = 0;
	info->screenheight = 0;
	info->number_of_sprite = 0;
	info->flag.key_w = 0;
	info->flag.key_s = 0;
	info->flag.key_a = 0;
	info->flag.key_d = 0;
	info->sprite_list = NULL;
}

void	print_graphic(t_gdata *graphic_info)
{
	printf("graphic_info->x_render_size : %d\n", graphic_info->x_render_size);
	printf("graphic_info->y_render_size : %d\n", graphic_info->y_render_size);
	printf("graphic_info->f_red : %d\n", graphic_info->f_red);
	printf("graphic_info->f_green : %d\n", graphic_info->f_green);
	printf("graphic_info->f_blue : %d\n", graphic_info->f_blue);
	printf("graphic_info->c_red : %d\n", graphic_info->c_red);
	printf("graphic_info->c_green : %d\n", graphic_info->c_green);
	printf("graphic_info->c_blue : %d\n", graphic_info->c_blue);
	printf("graphic_info->path_to_the_north_texture : %s\n", graphic_info->path_to_the_north_texture);
	printf("graphic_info->path_to_the_south_texture : %s\n", graphic_info->path_to_the_south_texture);
	printf("graphic_info->path_to_the_west_texture : %s\n", graphic_info->path_to_the_west_texture);
	printf("graphic_info->path_to_the_east_texture : %s\n", graphic_info->path_to_the_east_texture);
	printf("graphic_info->path_to_the_sprite_texture : %s\n", graphic_info->path_to_the_sprite_texture);
}

void	print_structure(t_hub *info)
{
	printf("x_render_size : %d\n", info->graphic->x_render_size);
	printf("y_render_size : %d\n", info->graphic->y_render_size);
	printf("path_to_the_north_texture : %s\n", info->graphic->path_to_the_north_texture);
	printf("path_to_the_south_texture : %s\n", info->graphic->path_to_the_south_texture);
	printf("path_to_the_west_texture : %s\n", info->graphic->path_to_the_west_texture);
	printf("path_to_the_east_texture : %s\n", info->graphic->path_to_the_east_texture);
	printf("path_to_the_sprite_texture : %s\n", info->graphic->path_to_the_sprite_texture);
	printf("f_red : %d\n", info->graphic->f_red);
	printf("f_green : %d\n", info->graphic->f_green);
	printf("f_blue : %d\n", info->graphic->f_blue);
	printf("c_red : %d\n", info->graphic->c_red);
	printf("c_green : %d\n", info->graphic->c_green);
	printf("c_blue : %d\n", info->graphic->c_blue);
	printf("posX : %f\n", info->posX);
	printf("posY : %f\n", info->posY);
	printf("dirX : %f\n", info->dirX);
	printf("dirY : %f\n", info->dirY);
	printf("planeX : %f\n", info->planeX);
	printf("planeY : %f\n", info->planeY);
	printf("moveSpeed : %f\n", info->moveSpeed);
	printf("rotationSpeed : %f\n", info->rotationSpeed);
}
/*
int	function_exit(int *error_flag)
{

}
*/
