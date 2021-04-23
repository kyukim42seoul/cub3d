#include "cub3D.h"

// 구조체 초기화 확인용 함수

/*void	set_map_info(t_info *map_information)
{
	map_information->x_render_size = 1920;
	map_information->y_render_size = 1080;
	map_information->floor_color = 255;
	map_information->ceiling_color = 100;
	map_information->path_to_the_north_texture = "./textures/north.xml";
	map_information->path_to_the_south_texture = "./textures/south.xml";
	map_information->path_to_the_west_texture = "./textures/west.xml";
	map_information->path_to_the_east_texture = "./textures/east.xml";
	map_information->path_to_the_sprite_texture = "./textures/sprite.xml";
}*/

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
	while (count-- > 0)
		free(source[count]);
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

int	parse_cub(char *source_line, t_info *map_information)
{
	int	count;
	char	**temp;
	char	**color_temp;

	count = 0;
	temp = ft_split(source_line, ' ');
	while (temp[count])
		count++;
	if (**temp == 'R')
	{
		map_information->x_render_size = cub_atoi(temp[1]);
		map_information->y_render_size = cub_atoi(temp[2]);
		free_by_count(temp, count);
	}
	else if (compare_text(temp[0], "NO"))
	{
		map_information->path_to_the_north_texture = ft_strdup(temp[1]);
		free_by_count(temp, count);
	}
	else if (compare_text(temp[0], "SO"))
	{
		map_information->path_to_the_south_texture = ft_strdup(temp[1]);
		free_by_count(temp, count);
	}
	else if (compare_text(temp[0], "WE"))
	{
		map_information->path_to_the_west_texture = ft_strdup(temp[1]);
		free_by_count(temp, count);
	}
	else if (compare_text(temp[0], "EA"))
	{
		map_information->path_to_the_east_texture = ft_strdup(temp[1]);
		free_by_count(temp, count);
	}
	else if (compare_text(temp[0], "S"))
	{
		map_information->path_to_the_sprite_texture = ft_strdup(temp[1]);
		free_by_count(temp, count);
	}
	else if (compare_text(temp[0], "F"))
	{
		color_temp = ft_split(temp[1], ',');
		map_information->f_red = cub_atoi(color_temp[0]);
		map_information->f_green = cub_atoi(color_temp[1]);
		map_information->f_blue = cub_atoi(color_temp[2]);
		free_by_count(color_temp, 3);
		free_by_count(temp, count);
	}
	else if (compare_text(temp[0], "C"))
	{
		color_temp = ft_split(temp[1], ',');
		map_information->c_red = cub_atoi(color_temp[0]);
		map_information->c_green = cub_atoi(color_temp[1]);
		map_information->c_blue = cub_atoi(color_temp[2]);
		free_by_count(color_temp, 3);
		free_by_count(temp, count);
	}
		return (1);
}
