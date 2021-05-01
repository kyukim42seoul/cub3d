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

int	check_structure(t_info *map_information)
{
	int	count;

	count = 0;
	if (map_information->x_render_size)
		count++;
	if (map_information->y_render_size)
		count++;
	if (map_information->f_red >= 0)
		count++;
	if (map_information->f_green >= 0)
		count++;
	if (map_information->f_blue >= 0)
		count++;
	if (map_information->c_red >= 0)
		count++;
	if (map_information->c_green >= 0)
		count++;
	if (map_information->c_blue >= 0)
		count++;
	if (map_information->path_to_the_north_texture)
		count++;
	if (map_information->path_to_the_south_texture)
		count++;
	if (map_information->path_to_the_west_texture)
		count++;
	if (map_information->path_to_the_east_texture)
		count++;
	if (map_information->path_to_the_sprite_texture)
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
	if (compare_text(temp[0], "R"))
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

int	start_parsing(t_info *map_information, char **map)
{
	t_list	*head;
	t_list	*now;
	char	*source_line;
	int		fd;
	int		y_map_size;
	int		x_map_size;
	int		map_index;
	int		check_count;

	printf("here\n");
	map_index = 0;
	y_map_size = 0;
	x_map_size = 0;
	check_count = 0;
	fd = open("./conf.cub", O_RDONLY);
	map_information = malloc(sizeof(t_info));
	reset_map_information(map_information);

	while (check_count != 13)
	{
		check_count = check_structure(map_information);
		get_next_line(fd, &source_line);
		if (*source_line != '\0')
			parse_cub(source_line, map_information);
	}
	head = ft_lstnew(NULL);
	while (get_next_line(fd, &source_line) == 1)
	{
		now = ft_lstnew((void *)source_line);
		if ((int)ft_strlen(now->content) > x_map_size)
			x_map_size = ft_strlen(now->content);
		y_map_size++;
		ft_lstadd_back(&head, now);
	}
	map = (char **)malloc(sizeof(char *) * (y_map_size + 1));
	now = head->next;
	while (now->next)
	{
		map[map_index] = ft_strdup((char *)now->content);
		printf("%s\n", map[map_index]);
		now = now->next;
		map_index++;
	}
	printf("x_map_size : %d\n", x_map_size);
	printf("y_map_size : %d\n", y_map_size);

	return (0);
}