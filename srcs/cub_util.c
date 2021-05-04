#include "cub3D.h"

void	reset_graphic_info(g_info *graphic_info)
{
	graphic_info->x_render_size = 0;
	graphic_info->y_render_size = 0;
	graphic_info->f_red = -1;
	graphic_info->f_green = -1;
	graphic_info->f_blue = -1;
	graphic_info->c_red = -1;
	graphic_info->c_green = -1;
	graphic_info->c_blue = -1;
	graphic_info->path_to_the_north_texture = 0;
	graphic_info->path_to_the_south_texture = 0;
	graphic_info->path_to_the_west_texture = 0;
	graphic_info->path_to_the_east_texture = 0;
	graphic_info->path_to_the_sprite_texture = 0;
}

void	print_structure(g_info *graphic_info)
{
	printf("x_render_size : %d\n", graphic_info->x_render_size);
	printf("y_render_size : %d\n", graphic_info->y_render_size);
	printf("path_to_the_north_texture : %s\n", graphic_info->path_to_the_north_texture);
	printf("path_to_the_south_texture : %s\n", graphic_info->path_to_the_south_texture);
	printf("path_to_the_west_texture : %s\n", graphic_info->path_to_the_west_texture);
	printf("path_to_the_east_texture : %s\n", graphic_info->path_to_the_east_texture);
	printf("path_to_the_sprite_texture : %s\n", graphic_info->path_to_the_sprite_texture);
	printf("f_red : %d\n", graphic_info->f_red);
	printf("f_green : %d\n", graphic_info->f_green);
	printf("f_blue : %d\n", graphic_info->f_blue);
	printf("c_red : %d\n", graphic_info->c_red);
	printf("c_green : %d\n", graphic_info->c_green);
	printf("c_blue : %d\n", graphic_info->c_blue);
}

