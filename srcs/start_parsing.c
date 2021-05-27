/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:59 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/28 01:16:35 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		complete_structure(t_graphic *g)
{
	if (!g->north)
		return (0);
	else if (!g->south)
		return (0);
	else if (!g->west)
		return (0);
	else if (!g->east)
		return (0);
	else if (!g->pathsprite)
		return (0);
	else if (!g->x_render_size)
		return (0);
	else if (!g->y_render_size)
		return (0);
	else if (g->floor_color == -1)
		return (0);
	else if (g->ceiling_color == -1)
		return (0);
	else
		return (1);
}

void			start_parsing(int fd, char ***map, t_info *info)
{
	int		count;
	char	*line;

	count = 0;
	while (!complete_structure(info->g))
	{
		get_next_line(fd, &line);
		if (!line)
			error_function("Fail get_next_line");
		if (*line != '\0')
		{
			parse_cub(line, info->g);
			free(line);
		}
		else
			free(line);
	}
	parse_map(fd, map, info);
	if (info->number_of_sprite == 0)
		error_function("Invaild Map No Sprite");
}
