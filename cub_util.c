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
