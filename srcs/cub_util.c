/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:07 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/27 21:15:16 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_by_count(char **source, int count)
{
	while (count-- > 0)
		free(source[count]);
	free(source);
}

void	error_function(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	exit(0);
}

int		compare_text(char *source_line, char *text)
{
	while (*text)
	{
		if (*source_line == *text)
		{
			source_line++;
			text++;
		}
		else
			return (0);
	}
	return (1);
}

void	combine_color(int *color, int red, int green, int blue)
{
	int	temp;

	temp = 0;
	temp |= red << 16;
	temp |= green << 8;
	temp |= blue;
	*color = temp;
}

void	free_texture_buf(t_hub *info)
{
	int	y;

	y = 0;
	while (y < info->scrn_h)
	{
		free(info->texture[y]);
		y++;
	}
	free(info->texture[y]);
	free(info->texture);
}
