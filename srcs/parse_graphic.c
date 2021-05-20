#include "cub3D.h"

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

static int	compare_text(char *source_line, char *text)
{
	while (*source_line || *text)
	{
		if (*source_line != *text)
			return (0);
		source_line++;
		text++;
	}
		return (1);
}

static void	free_by_count(char **source, int count)
{
	static int	checking = 0;
	while (count-- > 0)
	{
//		printf("%d %d\n", count, checking);
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
		source++;
	}
	return (number);
}

int	parse_cub(char *source_line, t_gdata *graphic_info)
{
	int	count;
	char	**temp;
	char	**color_temp;

	count = 0;
	temp = ft_split(source_line, ' ');
	while (temp[count])
		count++;
	if (compare_text(temp[0], "R"))
	{
		graphic_info->x_render_size = cub_atoi(temp[1]);
		graphic_info->y_render_size = cub_atoi(temp[2]);
		free_by_count(temp, count);
	}
	else if (compare_text(temp[0], "NO"))
	{
		graphic_info->path_to_the_north_texture = ft_strdup(temp[1]);
		free_by_count(temp, count);
	}
	else if (compare_text(temp[0], "SO"))
	{
		graphic_info->path_to_the_south_texture = ft_strdup(temp[1]);
		free_by_count(temp, count);
	}
	else if (compare_text(temp[0], "WE"))
	{
		graphic_info->path_to_the_west_texture = ft_strdup(temp[1]);
		free_by_count(temp, count);
	}
	else if (compare_text(temp[0], "EA"))
	{
		graphic_info->path_to_the_east_texture = ft_strdup(temp[1]);
		free_by_count(temp, count);
	}
	else if (compare_text(temp[0], "S"))
	{
		graphic_info->path_to_the_sprite_texture = ft_strdup(temp[1]);
		free_by_count(temp, count);
	}
	else if (compare_text(temp[0], "F"))
	{
		color_temp = ft_split(temp[1], ',');
		graphic_info->f_red = cub_atoi(color_temp[0]);
		graphic_info->f_green = cub_atoi(color_temp[1]);
		graphic_info->f_blue = cub_atoi(color_temp[2]);
		combine_color(&graphic_info->floor_color, graphic_info->f_red, graphic_info->f_green, graphic_info->f_blue);
		printf("%d\n", graphic_info->floor_color);
		free_by_count(color_temp, 3);
		free_by_count(temp, count);
	}
	else if (compare_text(temp[0], "C"))
	{
		color_temp = ft_split(temp[1], ',');
		graphic_info->c_red = cub_atoi(color_temp[0]);
		graphic_info->c_green = cub_atoi(color_temp[1]);
		graphic_info->c_blue = cub_atoi(color_temp[2]);
		combine_color(&graphic_info->ceiling_color, graphic_info->c_red, graphic_info->c_green, graphic_info->c_blue);
		printf("%d\n", graphic_info->ceiling_color);
		free_by_count(color_temp, 3);
		free_by_count(temp, count);
	}
	return (1);
}
