/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_efficiency.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:43 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/28 01:16:13 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		check_y(t_info *info, char **map, int y, int x)
{
	if (y != 0 && map[y - 1][x] != ' ' && map[y - 1][x] != '1')
		return (1);
	else if (y != (info->map_height - 1)\
	&& map[y + 1][x] != ' ' && map[y + 1][x] != '1')
		return (1);
	else
		return (0);
}

static int		check_cross(t_info *info, char **map, int y, int x)
{
	int	check;

	check = 0;
	if (x != 0 && map[y][x - 1] != ' ' && map[y][x - 1] != '1')
		check++;
	else if (x != (info->map_width - 1)\
	&& map[y][x + 1] != ' ' && map[y][x + 1] != '1')
		check++;
	check += check_y(info, map, y, x);
	return (check);
}

void			check_boundary(t_info *info, char **map)
{
	int	check;
	int	y;
	int	x;

	check = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (x == 0 || y == 0 ||\
			x == (info->map_width - 1) || y == (info->map_height - 1))
				if (map[y][x] != ' ' && map[y][x] != '1')
					return (error_function("Invalid Map"));
			if (map[y][x] == ' ')
				check += check_cross(info, map, y, x);
			x++;
		}
		y++;
	}
	if (check > 0)
		return (error_function("Invaild Map"));
}
