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

void	set_sprite_distance(t_character c, t_sprite_list *node)
{
	while (node)
	{
		node->distance = (c.posX - node->x) * (c.posX - node->x) + (c.posY - node->y) * (c.posY - node->y);
		node = node->next;
	}
}

int	main_loop(t_hub *info)
{
	key_update(info);
	dda(info);
	set_sprite_distance(info->c, info->sprite_list->next);
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

static void	basic_process(t_hub info, char **argv)
{
	int	fd;

	fd = 0;
	fd = open(argv[1], O_RDONLY);
	start_parsing(fd, &info.map, &info);
	info.mlx = mlx_init();
	info.screenwidth = info.g->x_render_size;
	info.screenheight = info.g->y_render_size;
	info.z = (double *)malloc(sizeof(double) * info.g->x_render_size);
	set_texture_buf(&info);
	set_screen_buf(&info);
	load_texture(&info);
	info.win = mlx_new_window(info.mlx, info.screenwidth, info.screenheight, "cub3D");
	info.img.img = mlx_new_image(info.mlx, info.screenwidth, info.screenheight);
	info.img.addr = (int *)mlx_get_data_addr(info.img.img, &info.img.bits_per_pixel, &info.img.size_line, &info.img.endian);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);
	mlx_loop(info.mlx);
}

int	main(int argc, char *argv[])
{
	t_hub		info;

	reset_hub(&info);
	if (argc < 2 || argc > 3)
		return (0);
	if (check_arguments(&info, argc, argv))
	{
		make_bitmap(argv, &info);
		return (0);
	}
	else
		basic_process(info, argv);
	return (0);
}
