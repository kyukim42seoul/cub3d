#include "cub3D.h"
/*
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
*/

static void	free_structure(t_hub *info)
{
	int	index;

	index = 0;
	free(info->graphic->path_to_the_north_texture);
	free(info->graphic->path_to_the_south_texture);
	free(info->graphic->path_to_the_west_texture);
	free(info->graphic->path_to_the_east_texture);
	while (info->map[index])
	{
		free(info->map[index]);
		index++;
	}
	free(info->graphic);
}

int	main(int argc, char *argv[])
{
	t_hub		info;
	int			fd;
	int			index;

	index = 0;
	info.map = 0;
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	info.graphic = malloc(sizeof(t_gdata));
	reset_info(&info);
	start_parsing(fd, &info.map, &info);
	if (info.error == 0)
	{
		print_structure(&info);
//		print_map(info.map);
	}
	else
		printf("%s\n", info.error_message);
	info.mlx = mlx_init();
	mlx_get_screen_size(info.mlx, &info.screenwide, &info.screenheight);
	info.win = mlx_new_window(info.mlx, info.screenwide, info.screenheight, "cub3D");
	info.image.img = mlx_new_image(info.mlx, info.screenwide, info.screenheight);
	info.image.addr = mlx_get_data_addr(info.image.img, &info.image.bits_per_pixel, &info.image.line_length, &info.image.endian);
	mlx_loop_hook(info.mlx, &dda, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_loop(info.mlx);
	free_structure(&info);
	return (0);
}
