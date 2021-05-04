#include "cub3D.h"

void	find_pos(char **map, tdda_info *vector)
{
	char	**temp;
	int	x;
	int	y;

	temp = 0;
	x = 0;
	y = 0;
	while (!temp && map[y])
	{
		if (ft_strchr(map[y], 'N'))
		{
			vector->pos->x ==
			vector->dir->x == 0;
			vector->dir->y == 1;
		}
		else if (ft_strchr(map[y],'S'))
		{
			vector->dir->x == 0;
			vector->dir->y == -1;
		}
		else if (ft_strchr(map[y], 'W'))
		{
			vector->dir->x == -1;
			vector->dir->y == 0;
		}
		else if (ft_strchr(map[y], 'E'))
		{
			vector->dir->x == 1;
			vector->dir->y == 0;
		}
		y++;
	}
}
