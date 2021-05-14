#include "cub3D.h"

void	set_pixel_color(t_hub *info, int x, int y, int color)
{
	char	*dst;

	dst = info->image.addr + (y * info->image.line_length + x * (info->image.bits_per_pixel / 8));

	*(unsigned int *)dst = color;
}

void	verline (t_hub *info, int x, int y1, int y2, int color)
{
	int	y;
	int	eyesight;

	eyesight = info->screenheight / 2;
	y = 0;
	while (y < eyesight)
	{
		set_pixel_color(info, x, y, 0x006699FF);
		y++;
	}
	while (y < info->screenheight)
	{
		set_pixel_color(info, x, y, 0x00996600);
		y++;

	}
	while (y1 < y2)
	{
		set_pixel_color(info, x, y1, color);
		y1++;
	}
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

