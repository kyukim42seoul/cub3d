#include "cub3D.h"

void	print_map(char **map)
{
	int	index;

	index = 0;
	while (map[index])
	{
		printf("|%s|\n", map[index]);
		index++;
	}
	printf("|%s|\n", map[index]);
}

/*
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
*/
/*
static void	free_structure(t_hub *info)
{
	int	index;

	index = 0;
	free(info->graphic->path_to_the_north_texture);
	free(info->graphic->path_to_the_south_texture);
	free(info->graphic->path_to_the_west_texture);
	free(info->graphic->path_to_the_east_texture);
	free(info->graphic->path_to_the_sky_texture);
	free(info->graphic->path_to_the_floor_texture);
	free(info->graphic->path_to_the_sprite_texture);

	while (info->map[index])
	{
		printf("%p %s\n", info->map[index], info->map[index]);
		free(info->map[index]);
		index++;
	}
	free(info->map[index]);
	free(info->map);
	free(info->graphic);
}
*/

void	set_sprite_distance(t_hub *info, t_sprite_list *node)
{
	while (node)
	{
		node->distance = (info->posX - node->x) * (info->posX - node->x) + (info->posY - node->y) * (info->posY - node->y);
		node = node->next;
	}
}

int	main_loop(t_hub *info)
{
	key_update(info);
	dda(info);
	set_sprite_distance(info, info->sprite_list->next);
	sort_sprite_node(info->sprite_list->next);
	draw_sprite(info);
	draw_image(info);
	return (0);
}

static	int	compare_string(char *dst, char *src)
{
	while (*dst)
	{
		if (*dst == *src)
		{
			dst++;
			src++;
		}
		else
			return (0);
	}
	return (1);
}

static	int	check_arguments(t_hub *info, int argc, char **argv)
{
	int	save;
	char	*temp;

	save = 0;
	temp = argv[1] + ft_strlen(argv[1]) - 4;
	if (argc == 2)
	{
		if (!compare_string(temp, ".cub"))
		{
			info->error_message = ft_strdup("Incollect .cub file\n");
			return (0);
		}
	}
	else if (argc == 3)
	{
		if (compare_string(argv[2], "--save") && ft_strlen(argv[2]) == 6)
			save = 1;
	}
	return (save);
}

int	main(int argc, char *argv[])
{
	t_hub		info;
	int			fd;

	reset_info(&info);
	fd = 0;
	if (argc < 2 || argc > 3)
		return (0);
	if (check_arguments(&info, argc, argv))
	{
		make_bitmap(argv, &info, fd);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
//	info.sprite = (t_sprite *)malloc(sizeof(t_sprite) * 3);
	start_parsing(fd, &info.map, &info);
	info.mlx = mlx_init();
	info.screenwide = info.graphic->x_render_size;
	info.screenheight = info.graphic->y_render_size;
	info.z = (double *)malloc(sizeof(double) * info.graphic->x_render_size);
	set_texture_buf(&info);
	set_screen_buf(&info);
	load_texture(&info);
	info.win = mlx_new_window(info.mlx, info.screenwide, info.screenheight, "cub3D");
	info.image.img = mlx_new_image(info.mlx, info.screenwide, info.screenheight);
	info.image.addr = (int *)mlx_get_data_addr(info.image.img, &info.image.bits_per_pixel, &info.image.line_length, &info.image.endian);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);
	mlx_loop(info.mlx);
//	free_structure(&info);
	return (0);
}
