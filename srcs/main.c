/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:40 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/28 05:48:44 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				main_loop(t_info *info)
{
	key_update(info);
	dda(info);
	set_sprite_distance(info->c, info->sprite_list->next);
	sort_sprite_node(info->sprite_list->next);
	draw_sprite(info);
	mlx_sync(1, info->img.img);
	draw_image(info);
	mlx_sync(3, info->win);
	return (0);
}

static	int		check_arguments(t_info *info, int argc, char **argv)
{
	char	*extension;

	extension = argv[1] + ft_strlen(argv[1]) - 4;
	if (!compare_text(extension, ".cub"))
		error_function("Invaild Extension .cub");
	if (argc == 3)
	{
		if (!compare_text(argv[2], "--save") || ft_strlen(argv[2]) != 6)
			error_function("Invaild Option");
		info->save = 1;
	}
	return (info->save);
}

static void		basic_process(t_info info, char **argv)
{
	info.fd = open(argv[1], O_RDONLY);
	if (info.fd < 0)
		error_function("Fail Open .cub");
	start_parsing(info.fd, &info.map, &info);
	info.mlx = mlx_init();
	check_render_size(&info);
	info.z = (double *)malloc(sizeof(double) * info.g->x_render_size);
	set_texture_buf(&info);
	set_screen_buf(&info);
	load_texture(&info);
	info.win = mlx_new_window(info.mlx, info.scrn_w, info.scrn_h, "cub3D");
	info.img.img = mlx_new_image(info.mlx, info.scrn_w, info.scrn_h);
	info.img.addr = (int *)mlx_get_data_addr(info.img.img,\
	&info.img.bits_per_pixel, &info.img.size_line, &info.img.endian);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);
	mlx_hook(info.win, X_EVENT_KEY_EXIT, 1L << 0, &exit_door, 0);
	mlx_loop(info.mlx);
}

int				main(int argc, char *argv[])
{
	t_info		info;

	reset_info(&info);
	if (argc < 2 || argc > 3)
		error_function("Invalid Argument Number");
	if (check_arguments(&info, argc, argv))
	{
		make_bitmap(argv, &info);
		return (0);
	}
	else
		basic_process(info, argv);
	return (0);
}
