/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_graphic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:45 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/27 21:50:25 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	cub_atoi(char *source)
{
	int	number;

	number = 0;
	if (*source == '0' && ft_strlen(source) == 1)
		return (0);
	if (*source < '1' || *source > '9')
		error_function("Invaild Number");
	while (*source)
	{
		if (*source >= '0' && *source <= '9')
			number = number * 10 + (*source - '0');
		else
			error_function("Invaild Number");
		source++;
	}
	return (number);
}

static void	set_texture_path(char **path, char **src, int count)
{
	char *extension;

	if (*path || count != 2)
		error_function("Invaild Texture Path");
	extension = src[1] + ft_strlen(src[1]) - 4;
	if (!compare_text(extension, ".xpm"))
		error_function("Invaild Extension .xpm");
	*path = ft_strdup(src[1]);
	free_by_count(src, count);
}

static void	set_color(int *color, char **src, int count)
{
	char	**palette;
	int		r;
	int		g;
	int		b;
	int		num;

	r = -1;
	g = -1;
	b = -1;
	num = 0;
	if (*color != -1 || count != 2)
		error_function("Invaild Color");
	palette = ft_split(src[1], ',');
	while (palette[num])
		num++;
	if (num != 3)
		error_function("Invaild Color");
	r = cub_atoi(palette[0]);
	g = cub_atoi(palette[1]);
	b = cub_atoi(palette[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_function("Invaild Color");
	combine_color(color, r, g, b);
	free_by_count(palette, 3);
	free_by_count(src, count);
}

static void	set_resolution(t_graphic *g, char **temp, int count)
{
	if (g->x_render_size > 0 || g->y_render_size > 0 || count != 3)
		error_function("Invaild Resolution");
	g->x_render_size = cub_atoi(temp[1]);
	g->y_render_size = cub_atoi(temp[2]);
	if (g->x_render_size == 0 || g->y_render_size == 0)
		error_function("Invaild Resolution");
	free_by_count(temp, count);
}

void		parse_cub(char *source_line, t_graphic *g)
{
	int		count;
	char	**temp;

	count = 0;
	temp = ft_split(source_line, ' ');
	while (temp[count])
		count++;
	if (compare_text(source_line, "R "))
		set_resolution(g, temp, count);
	else if (compare_text(source_line, "NO "))
		set_texture_path(&g->north, temp, count);
	else if (compare_text(source_line, "SO "))
		set_texture_path(&g->south, temp, count);
	else if (compare_text(source_line, "WE "))
		set_texture_path(&g->west, temp, count);
	else if (compare_text(source_line, "EA "))
		set_texture_path(&g->east, temp, count);
	else if (compare_text(source_line, "S "))
		set_texture_path(&g->pathsprite, temp, count);
	else if (compare_text(source_line, "F "))
		set_color(&g->floor_color, temp, count);
	else if (compare_text(source_line, "C "))
		set_color(&g->ceiling_color, temp, count);
	else
		error_function("Invaild Identifier");
}
