#include "cub3D.h"

int	key_update(t_hub *info)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = 0;
	oldPlaneX = 0;
	if (info->flag.key_esc == 1)
		exit(0);
	if (info->flag.key_w == 1)
	{
		if (info->map[(int)info->posY][(int)(info->posX + info->dirX * info->moveSpeed)] == '0')
			info->posX += info->dirX * info->moveSpeed;
		if (info->map[(int)(info->posY + info->dirY * info->moveSpeed)][(int)info->posX] == '0')
			info->posY += info->dirY * info->moveSpeed;
	}
	if (info->flag.key_s == 1)
	{
		if (info->map[(int)info->posY][(int)(info->posX - info->dirX * info->moveSpeed)] == '0')
			info->posX -= info->dirX * info->moveSpeed;
		if (info->map[(int)(info->posY - info->dirY * info->moveSpeed)][(int)info->posX] == '0')
			info->posY -= info->dirY * info->moveSpeed;
	}
	if (info->flag.key_a == 1)
	{
		oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotationSpeed) - info->dirY * sin(-info->rotationSpeed);
		info->dirY = oldDirX * sin(-info->rotationSpeed) + info->dirY * cos(-info->rotationSpeed);
		oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotationSpeed) - info->planeY * sin(-info->rotationSpeed);
		info->planeY = oldPlaneX * sin(-info->rotationSpeed) + info->planeY * cos(-info->rotationSpeed);
	}
	if (info->flag.key_d == 1)
	{
		oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotationSpeed) - info->dirY * sin(info->rotationSpeed);
		info->dirY = oldDirX * sin(info->rotationSpeed) + info->dirY * cos(info->rotationSpeed);
		oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotationSpeed) - info->planeY * sin(info->rotationSpeed);
		info->planeY = oldPlaneX * sin(info->rotationSpeed) + info->planeY * cos(info->rotationSpeed);
	}
	return (0);
}

int	key_release(int key, t_hub *info)
{
	if (key == KEY_W)
		info->flag.key_w = 0;
	if (key == KEY_S)
		info->flag.key_s = 0;
	if (key == KEY_A)
		info->flag.key_a = 0;
	if (key == KEY_D)
		info->flag.key_d = 0;
	return (0);
}


int	key_press(int key, t_hub *info)
{
	if (key == KEY_W)
		info->flag.key_w = 1;
	if (key == KEY_S)
		info->flag.key_s = 1;
	if (key == KEY_D)
		info->flag.key_d = 1;
	if (key == KEY_A)
		info->flag.key_a = 1;
	if (key == KEY_ESC)
		info->flag.key_esc = 1;
	return (0);
}
