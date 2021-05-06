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

static void	print_map(char **map)
{
	int	index;

	index = 0;
	while (map[index])
	{
		printf("%s\n", map[index]);
		index++;
	}
}

static void	set_info(t_hub **info)
{
	*info = malloc(sizeof(t_hub));
	(*info)->graphic = malloc(sizeof(g_info));
	(*info)->vector = malloc(sizeof(tdda_info));
	(*info)->vector->pos = malloc(sizeof(v_info));
	(*info)->vector->dir = malloc(sizeof(v_info));
	(*info)->vector->rayDir = malloc(sizeof(v_info));
	(*info)->vector->plane = malloc(sizeof(v_info));
	(*info)->vector->sideDist = malloc(sizeof(v_info));
	(*info)->vector->deltaDist = malloc(sizeof(v_info));
}

int	main(int argc, char *argv[])
{
	t_hub		*info;
	char		**map;
	void		*mlx_pointer;
	void		*mlx_window;
	int			fd;

	map = 0;
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	set_info(&info);
	reset_info(info);
	start_parsing(fd, &map, info);
	if (info->error == 0)
	{
		print_structure(info->graphic);
		print_map(map);
	}
	else
		printf("%s\n", info->error_message);
	mlx_pointer = mlx_init();
	mlx_window = mlx_new_window(mlx_pointer, 1920, 1080, "cub3D");

	mlx_loop(mlx_pointer);
	return (0);
}
