/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:07 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/28 06:17:16 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_door(void)
{
	exit(0);
}

void	error_function(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	exit(0);
}

void	free_by_count(char **source, int count)
{
	while (count-- > 0)
		free(source[count]);
	free(source);
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
