#include "cub3D.h"

static void	reset_graphic(t_graphic **g)
{
	*g = (t_graphic *)malloc(sizeof(t_graphic));
	if (!*g)
		error_function("Fail Malloc");
	(*g)->x_render_size = 0;
	(*g)->y_render_size = 0;
	(*g)->path_to_the_north_texture = 0;
	(*g)->path_to_the_south_texture = 0;
	(*g)->path_to_the_west_texture = 0;
	(*g)->path_to_the_east_texture = 0;
	(*g)->path_to_the_sprite_texture = 0;
	(*g)->ceiling_color = -1;
	(*g)->floor_color = -1;
}

static void	reset_character(t_character *c)
{
	c->posX = 0;
	c->posY = 0;
	c->dirX = 0;
	c->dirY = 0;
	c->planeX = 0;
	c->planeY = 0;
	c->moveSpeed = 0.05;
	c->rotationSpeed = 0.05;
}

static void	reset_sysinfo(t_hub *info)
{
	info->img.img = 0;
	info->img.addr = 0;
	info->img.bits_per_pixel = 0;
	info->img.size_line = 0;
	info->img.endian = 0;
	info->img.img_height = 0;
	info->img.img_width = 0;
	info->k.w = 0;
	info->k.s = 0;
	info->k.a = 0;
	info->k.d = 0;
	info->error = 0;
	info->error_message = 0;
	info->mlx = 0;
	info->win = 0;
	info->screenwidth = 0;
	info->screenheight = 0;
}

static void	reset_mapinfo(t_hub *info)
{
	info->map = 0;
	info->map_width = 0;
	info->map_height = 0;
	info->number_of_sprite = 0;
	info->sprite_list = NULL;
}

void	reset_hub(t_hub *info)
{
	reset_sysinfo(info);
	reset_graphic(&info->g);
	reset_character(&info->c);
	reset_mapinfo(info);
}