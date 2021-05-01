#include "cub3D.h"

void	reset_map_information(t_info *map_information)
{
	map_information->x_render_size = 0;
	map_information->y_render_size = 0;
	map_information->f_red = -1;
	map_information->f_green = -1;
	map_information->f_blue = -1;
	map_information->c_red = -1;
	map_information->c_green = -1;
	map_information->c_blue = -1;
	map_information->path_to_the_north_texture = 0;
	map_information->path_to_the_south_texture = 0;
	map_information->path_to_the_west_texture = 0;
	map_information->path_to_the_east_texture = 0;
	map_information->path_to_the_sprite_texture = 0;
}

void	print_structure(t_info *map_information)
{
	printf("x_render_size : %d\n", map_information->x_render_size);
	printf("y_render_size : %d\n", map_information->y_render_size);
	printf("path_to_the_north_texture : %s\n", map_information->path_to_the_north_texture);
	printf("path_to_the_south_texture : %s\n", map_information->path_to_the_south_texture);
	printf("path_to_the_west_texture : %s\n", map_information->path_to_the_west_texture);
	printf("path_to_the_east_texture : %s\n", map_information->path_to_the_east_texture);
	printf("path_to_the_sprite_texture : %s\n", map_information->path_to_the_sprite_texture);
	printf("f_red : %d\n", map_information->f_red);
	printf("f_green : %d\n", map_information->f_green);
	printf("f_blue : %d\n", map_information->f_blue);
	printf("c_red : %d\n", map_information->c_red);
	printf("c_green : %d\n", map_information->c_green);
	printf("c_blue : %d\n", map_information->c_blue);
}

