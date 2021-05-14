#include "cub3D.h"

int	dda(t_hub *info)
{
	int	x;
	int	mapX;
	int	mapY;
	int	stepX;
	int	stepY;
	int	hit;
	int	side;
	int	lineHeight;
	double	rayDirX;
	double	rayDirY;
	double	cameraX;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;

	x = 0;
	while (x < info->screenwide)
	{
		cameraX = 2 * x / (double)info->screenwide - 1;
		rayDirX = info->dirX + info->planeX * cameraX;
		rayDirY = info->dirY + info->planeY * cameraX;

		mapX = (int)info->posX;
		mapY = (int)info->posY;

		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);

		hit = 0;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1 - info->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1 - info->posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (info->map[mapX][mapY] > '0')
				hit = 1;
		}
			if (rayDirX == 0)
			perpWallDist = sideDistX;
		else if (rayDirY == 0)
			perpWallDist = sideDistY;
		else
		{
			if (side == 0)
				perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;
		}
		lineHeight = (int)(info->screenheight / perpWallDist);
		int	drawStart = (-lineHeight / 2) + (info->screenheight / 2);
		if (drawStart < 0)
			drawStart = 0;
		int	drawEnd = (lineHeight / 2) + (info->screenheight / 2);
		if (drawEnd >= info->screenheight)
			drawEnd = info->screenheight - 1;

		int color;
		if (info->map[mapX][mapY] == '1')
			color = 0xFF0000;
		else
			color = 0x123145;

		if (side == 1)
			color = color / 2;
		verline(info, x, drawStart, drawEnd, color);
		x++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->image.img, 0, 0);
	return (0);
}

int	key_press(int key, t_hub *info)
{
	if (key == KEY_W)
	{
		if (info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)info->posY] == '0')
			info->posX += info->dirX * info->moveSpeed;
		if (info->map[(int)info->posX][(int)(info->posY + info->dirY * info->moveSpeed)] == '0')
			info->posY += info->dirY * info->moveSpeed;
	}
	if (key == KEY_S)
	{
		if (info->map[(int)(info->posX - info->dirX * info->moveSpeed)][(int)info->posY] == '0')
			info->posX -= info->dirX * info->moveSpeed;
		if (info->map[(int)info->posX][(int)(info->posY - info->dirY * info->moveSpeed)] == '0')
			info->posY -= info->dirY * info->moveSpeed;
	}
	if (key == KEY_A)
	{
		double	oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotationSpeed) - info->dirY * sin(info->rotationSpeed);
		info->dirY = oldDirX * sin(info->rotationSpeed) + info->dirY * cos(info->rotationSpeed);
		double	oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotationSpeed) - info->planeY * sin(info->rotationSpeed);
		info->planeY = oldPlaneX * sin(info->rotationSpeed) + info->planeY * cos(info->rotationSpeed);
	}
	if (key == KEY_D)
	{
		double	oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotationSpeed) - info->dirY * sin(-info->rotationSpeed);
		info->dirY = oldDirX * sin(-info->rotationSpeed) + info->dirY * cos(-info->rotationSpeed);
		double	oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotationSpeed) - info->planeY * sin(-info->rotationSpeed);
		info->planeY = oldPlaneX * sin(-info->rotationSpeed) + info->planeY * cos(-info->rotationSpeed);
	}
	if (key == KEY_ESC)
		exit(0);
	return (0);
}
