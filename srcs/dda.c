#include "cub3D.h"

int	dda(char **map, tdda_info *v)
{
	int	n;
	int	screen_wide;
	double	cameraX;
	double	perpWall;

	n = 0;
	screen_wide = 1920;
	v->pos->x = 22;
	v->pos->y = 23;
	v->dir->x = 0;
	v->dir->y = 1;
	v->plane->x = 0.66;
	v->plane->y = 1;

	while(1)
	{
		while (n < screen_wide)
		{
			cameraX = 2 * n / (double)screen_wide - 1;
			v->rayDir->x = v->dir->x + v->plane->x * cameraX;
			v->rayDir->y = v->dir->y + v->plane->y * cameraX;

			n++;
		}
	}
	return (0);
}
