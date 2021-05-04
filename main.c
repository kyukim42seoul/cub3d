#include "cub3D.h"

static void	print_structure(g_info *graphic_info)
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
static void	set_structures(g_info **graphic_info, tdda_info **vector)
{
	*graphic_info = malloc(sizeof(g_info));
	*vector = malloc(sizeof(tdda_info));
	(*vector)->pos = malloc(sizeof(v_info));
	(*vector)->dir = malloc(sizeof(v_info));
	(*vector)->rayDir = malloc(sizeof(v_info));
	(*vector)->plane = malloc(sizeof(v_info));
	(*vector)->sideDist = malloc(sizeof(v_info));
	(*vector)->deltaDist = malloc(sizeof(v_info));
}

int	main(/*int argc, char *argv[]*/)
{
	g_info	*graphic_info;
	t_list	*head;
	t_list	*now;
	tdda_info	*vectors;
	char	**map;
	void	*mlx_pointer;
	void	*mlx_window;
	int		fd;
	char	*source_line;
	int		y_map_size;
	int		x_map_size;
	int		map_index;
	int		check_count;
	int		x;
	int		y;

	x = 0;
	y = 0;
	map = 0;
	map_index = 0;
	y_map_size = 0;
	x_map_size = 0;
	check_count = 0;
	fd = open("./conf.cub", O_RDONLY);
	set_structures(&graphic_info, &vectors);
	reset_graphic_info(graphic_info);
	while (check_count != 13)
	{
		check_count = check_structure(graphic_info);
		get_next_line(fd, &source_line);
		if (*source_line != '\0')
			parse_cub(source_line, graphic_info);
	}
	print_structure(graphic_info);
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

	mlx_pointer = mlx_init();
	mlx_window = mlx_new_window(mlx_pointer, 1920, 1080, "cub3D");

	mlx_loop(mlx_pointer);
	return (0);
}
