/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:40 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/27 23:35:28 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int				main_loop(t_hub *info)
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

static	int		check_arguments(t_hub *info, int argc, char **argv)
{
	char	*extension;

	extension = argv[1] + ft_strlen(argv[1]) - 4;
	if (argc >= 2)
		if (!compare_text(extension, ".cub"))
			error_function("Invaild Extension .cub");
	if (argc == 3)
		if (compare_text(argv[2], "--save") && ft_strlen(argv[2]) == 6)
			info->save = 1;
	return (info->save);
}

static void		basic_process(t_hub info, char **argv)
{
	int	fd;

	fd = 0;
	fd = open(argv[1], O_RDONLY);
	start_parsing(fd, &info.map, &info);
	info.mlx = mlx_init();
	check_render_size(&info);
	info.z = (double *)malloc(sizeof(double) * info.g->x_render_size);
	set_texture_buf(&info);
	set_screen_buf(&info);
	load_texture(&info);
	info.win = mlx_new_window(info.mlx, info.scrn_w, info.scrn_h, "cub3D");
	info.img.img = mlx_new_image(info.mlx, info.scrn_w, info.scrn_h);
	info.img.addr = (int *)mlx_get_data_addr(info.img.img,\
	&info.img.bits_per_pixel,\
	&info.img.size_line, &info.img.endian);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);
	mlx_loop(info.mlx);
}

int				main(int argc, char *argv[])
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
