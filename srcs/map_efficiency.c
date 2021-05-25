#include "cub3D.h"

static int	check_x(t_hub *info, char **map, int y, int x)
{
	if (x != 0 && map[y][x - 1] != ' ' && map[y][x - 1] != '1')
		return (1);
	else if (x != (info->map_width - 1) && map[y][x + 1] != ' ' && map[y][x + 1] != '1')
		return (1);
	else
		return (0);
}

static int	check_y(t_hub *info, char **map, int y, int x)
{
	if (y != 0 && map[y - 1][x] != ' ' && map[y - 1][x] != '1')
		return (1);
	else if (y != (info->map_height - 1) && map[y + 1][x] != ' ' && map[y + 1][x] != '1')
		return (1);
	else
		return (0);
}

void	check_boundary(t_hub *info, char **map)
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
			if (x == 0 || y == 0 || x == (info->map_width - 1) || y == (info->map_height - 1))
				if (map[y][x] != ' ' && map[y][x] != '1')
					return (error_function("Invalid_Map"));
			if (map[y][x] == ' ')
			{
				check += check_x(info, map, y, x);
				check += check_y(info, map, y, x);
			}
			x++;
		}
		y++;
	}
	if (check > 0)
		return (error_function("Invaild_Map"));
}
