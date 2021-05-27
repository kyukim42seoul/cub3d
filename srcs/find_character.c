/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_character.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 17:11:45 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/28 06:08:26 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	its_north(int map_h, int index, char *line, t_character *c)
{
	c->pos_x = (double)index + 0.5;
	c->pos_y = (double)map_h + 0.5;
	c->dir_x = 0;
	c->dir_y = -1;
	c->plane_x = 0.66;
	c->plane_y = 0;
	*line = '0';
	c->cnt++;
}

static void	its_south(int map_h, int index, char *line, t_character *c)
{
	c->pos_x = (double)index + 0.5;
	c->pos_y = (double)map_h + 0.5;
	c->dir_x = 0;
	c->dir_y = 1;
	c->plane_x = -0.66;
	c->plane_y = 0;
	*line = '0';
	c->cnt++;
}

static void	its_west(int map_h, int index, char *line, t_character *c)
{
	c->pos_x = (double)index + 0.5;
	c->pos_y = (double)map_h + 0.5;
	c->dir_x = -1;
	c->dir_y = 0;
	c->plane_x = 0;
	c->plane_y = -0.66;
	*line = '0';
	c->cnt++;
}

static void	its_east(int map_h, int index, char *line, t_character *c)
{
	c->pos_x = (double)index + 0.5;
	c->pos_y = (double)map_h + 0.5;
	c->dir_x = 1;
	c->dir_y = 0;
	c->plane_x = 0;
	c->plane_y = 0.66;
	*line = '0';
	c->cnt++;
}

void		find_character(int map_h, char *line, t_character *c)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == 'N')
			its_north(map_h, index, &line[index], c);
		if (line[index] == 'S')
			its_south(map_h, index, &line[index], c);
		if (line[index] == 'W')
			its_west(map_h, index, &line[index], c);
		if (line[index] == 'E')
			its_east(map_h, index, &line[index], c);
		if (!check_char(line[index], " 012"))
			error_function("Invaild Map");
		index++;
	}
}
