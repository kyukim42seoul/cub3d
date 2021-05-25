#include "cub3D.h"
/*
int	check_structure(t_gdata *graphic_info)
{
	int	count;

	count = 0;
	if (graphic_info->x_render_size)
		count++;
	if (graphic_info->y_render_size)
		count++;
	if (graphic_info->f_red >= 0)
		count++;
	if (graphic_info->f_green >= 0)
		count++;
	if (graphic_info->f_blue >= 0)
		count++;
	if (graphic_info->c_red >= 0)
		count++;
	if (graphic_info->c_green >= 0)
		count++;
	if (graphic_info->c_blue >= 0)
		count++;
	if (graphic_info->path_to_the_north_texture)
		count++;
	if (graphic_info->path_to_the_south_texture)
		count++;
	if (graphic_info->path_to_the_west_texture)
		count++;
	if (graphic_info->path_to_the_east_texture)
		count++;
	if (graphic_info->path_to_the_sprite_texture)
		count++;
	return (count);
}
*/
static int	compare_text(char *source_line, char *text)
{
	while (*text)
	{
		if (*source_line == *text)
		{
			source_line++;
			text++;
		}
		else
			return (0);
	}
	return (1);
}

static void	free_by_count(char **source, int count)
{
	static int	checking = 0;
	while (count-- > 0)
	{
		free(source[count]);
		checking++;
	}
	free(source);
}

static int	cub_atoi(char *source)
{
	int	number;

	number = 0;
	while (*source)
	{
		if (*source >= '0' && *source <= '9')
			number = number * 10 + (*source - '0');
		else
			return (-1);
		source++;
	}
	return (number);
}

static int	set_texture_path(char **path, char **src, int count)
{
	if (*path)
		error_function("Invaild_Texture");
	*path = ft_strdup(src[1]);
	free_by_count(src, count);
	return (0);
}

static int	set_color(int *color, char **src, int count)
{
	char	**temp;
	int	r;
	int	g;
	int	b;
	int	index;

	r = -1;
	g = -1;
	b = -1;
	index = 0;
	if (*color != -1)
		error_function("Invaild_Color");
	temp = ft_split(src[1], ',');
	while (temp[index])
		index++;
	if (index != 3)
		error_function("Invaild_Color");
	r = cub_atoi(temp[0]);
	g = cub_atoi(temp[1]);
	b = cub_atoi(temp[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_function("Invaild_Color");
	combine_color(color, r, g, b);
	free_by_count(temp, 3);
	free_by_count(src, count);
	return (0);
}

static int	set_resolution(t_gdata *graphic, char **temp, int count)
{
	if (graphic->x_render_size || graphic->y_render_size)
		error_function("Invaild_Resolution");
	graphic->x_render_size = cub_atoi(temp[1]);
	graphic->y_render_size = cub_atoi(temp[2]);
	free_by_count(temp, count);
	return (0);
}

int	parse_cub(char *source_line, t_gdata *graphic)
{
	int	count;
	char	**temp;

	count = 0;
	temp = ft_split(source_line, ' ');
	while (temp[count])
		count++;
	if (compare_text(source_line, "R "))
		set_resolution(graphic, temp, count);
	else if (compare_text(source_line, "NO "))
		set_texture_path(&graphic->path_to_the_north_texture, temp, count);
	else if (compare_text(source_line, "SO "))
		set_texture_path(&graphic->path_to_the_south_texture, temp, count);
	else if (compare_text(source_line, "WE "))
		set_texture_path(&graphic->path_to_the_west_texture, temp, count);
	else if (compare_text(source_line, "EA "))
		set_texture_path(&graphic->path_to_the_east_texture, temp, count);
	else if (compare_text(source_line, "S "))
		set_texture_path(&graphic->path_to_the_sprite_texture, temp, count);
	else if (compare_text(source_line, "F "))
		set_color(&graphic->floor_color, temp, count);
	else if (compare_text(source_line, "C "))
		set_color(&graphic->ceiling_color, temp, count);
	else
		error_function("Invaild Identifier");
	return (1);
}
