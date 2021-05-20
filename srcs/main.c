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

int	main_loop(t_hub *info)
{
	key_update(info);
	dda(info);
	draw_sprite(info);
	draw_image(info);
	return (0);
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
	info.sprite = (t_sprite *)malloc(sizeof(t_sprite) * 3);
	start_parsing(fd, &info.map, &info);
/*-----------------------------for test
	if (info.error == 0)
	{
		print_structure(&info);
		print_map(info.map);
	}
	else
		printf("%s\n", info.error_message);
-----------------------------*/
	info.mlx = mlx_init();
//	mlx_get_screen_size(info.mlx, &info.screenwide, &info.screenheight);
/*-----------------------------for test
	int			check = 0;
	printf("%d\n", info.number_of_sprite);
	while (check < info.number_of_sprite)
	{
		printf("%d %f %f\n", check, info.sprite[check].x, info.sprite[check].y);
		check++;
	}
-----------------------------*/
	info.screenwide = info.graphic->x_render_size;
	info.screenheight = info.graphic->y_render_size;
	printf("start: %d\n", info.screenheight);
	info.z = (double *)malloc(sizeof(double) * info.graphic->x_render_size);
	set_texture_buf(&info);
	set_screen_buf(&info);
	load_texture(&info);

//-------------------------
/*
	t_idata		test;
	void		*win_2;
	int			y = 0;
	int			x = 0;
	win_2 = mlx_new_window(info.mlx, 100, 100, "test");
	test.img = mlx_new_image(info.mlx, 100, 100);
	test.addr = (int *)mlx_get_data_addr(test.img, &test.bits_per_pixel, &test.line_length, &test.endian);
	while (y < 64)
	{
		while (x < 64)
		{
			test.addr[y * 64 + x] = info.texture[0][y * 64 + x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info.mlx, win_2, test.img, 0, 0);
*/
//-------------------------
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
