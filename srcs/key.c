#include "cub3D.h"

int	key_update(t_hub *info)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = 0;
	oldPlaneX = 0;
	if (info->k.esc == 1)
		exit(0);
	if (info->k.w == 1)
	{
		if (info->map[(int)info->c.posY][(int)(info->c.posX + info->c.dirX * info->c.moveSpeed)] == '0')
			info->c.posX += info->c.dirX * info->c.moveSpeed;
		if (info->map[(int)(info->c.posY + info->c.dirY * info->c.moveSpeed)][(int)info->c.posX] == '0')
			info->c.posY += info->c.dirY * info->c.moveSpeed;
	}
	if (info->k.s == 1)
	{
		if (info->map[(int)info->c.posY][(int)(info->c.posX - info->c.dirX * info->c.moveSpeed)] == '0')
			info->c.posX -= info->c.dirX * info->c.moveSpeed;
		if (info->map[(int)(info->c.posY - info->c.dirY * info->c.moveSpeed)][(int)info->c.posX] == '0')
			info->c.posY -= info->c.dirY * info->c.moveSpeed;
	}
	if (info->k.a == 1)
	{
		oldDirX = info->c.dirX;
		info->c.dirX = info->c.dirX * cos(-info->c.rotationSpeed) - info->c.dirY * sin(-info->c.rotationSpeed);
		info->c.dirY = oldDirX * sin(-info->c.rotationSpeed) + info->c.dirY * cos(-info->c.rotationSpeed);
		oldPlaneX = info->c.planeX;
		info->c.planeX = info->c.planeX * cos(-info->c.rotationSpeed) - info->c.planeY * sin(-info->c.rotationSpeed);
		info->c.planeY = oldPlaneX * sin(-info->c.rotationSpeed) + info->c.planeY * cos(-info->c.rotationSpeed);
	}
	if (info->k.d == 1)
	{
		oldDirX = info->c.dirX;
		info->c.dirX = info->c.dirX * cos(info->c.rotationSpeed) - info->c.dirY * sin(info->c.rotationSpeed);
		info->c.dirY = oldDirX * sin(info->c.rotationSpeed) + info->c.dirY * cos(info->c.rotationSpeed);
		oldPlaneX = info->c.planeX;
		info->c.planeX = info->c.planeX * cos(info->c.rotationSpeed) - info->c.planeY * sin(info->c.rotationSpeed);
		info->c.planeY = oldPlaneX * sin(info->c.rotationSpeed) + info->c.planeY * cos(info->c.rotationSpeed);
	}
	return (0);
}

int	key_release(int key, t_hub *info)
{
	if (key == KEY_W)
		info->k.w = 0;
	if (key == KEY_S)
		info->k.s = 0;
	if (key == KEY_A)
		info->k.a = 0;
	if (key == KEY_D)
		info->k.d = 0;
	return (0);
}


int	key_press(int key, t_hub *info)
{
	if (key == KEY_W)
		info->k.w = 1;
	if (key == KEY_S)
		info->k.s = 1;
	if (key == KEY_D)
		info->k.d = 1;
	if (key == KEY_A)
		info->k.a = 1;
	if (key == KEY_ESC)
		info->k.esc = 1;
	return (0);
}
