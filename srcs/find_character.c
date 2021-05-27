/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_character.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 17:11:45 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/27 22:53:20 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	its_north(int map_h, int index, char *line, t_character *c)
{
	c->posX = (double)index + 0.5;
	c->posY = (double)map_h + 0.5;
	c->dirX = 0;
	c->dirY = -1;
	c->planeX = 0.66;
	c->planeY = 0;
	*line = '0';
	c->cnt++;
}

static void	its_south(int map_h, int index, char *line, t_character *c)
{
	c->posX = (double)index + 0.5;
	c->posY = (double)map_h + 0.5;
	c->dirX = 0;
	c->dirY = 1;
	c->planeX = -0.66;
	c->planeY = 0;
	*line = '0';
	c->cnt++;
}

static void	its_west(int map_h, int index, char *line, t_character *c)
{
	c->posX = (double)index + 0.5;
	c->posY = (double)map_h + 0.5;
	c->dirX = -1;
	c->dirY = 0;
	c->planeX = 0;
	c->planeY = -0.66;
	*line = '0';
	c->cnt++;
}

static void	its_east(int map_h, int index, char *line, t_character *c)
{
	c->posX = (double)index + 0.5;
	c->posY = (double)map_h + 0.5;
	c->dirX = 1;
	c->dirY = 0;
	c->planeX = 0;
	c->planeY = 0.66;
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
