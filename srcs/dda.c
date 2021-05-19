#include "cub3D.h"

int	main_loop(t_hub *info)
{
	dda(info);
	draw_image(info);
	return (0);
}

static	void	stepX_sideDist_by_rayDir(t_hub *info, t_var *var)
{
	if (var->rayDirX < 0)
	{
		var->stepX = -1;
		var->sideDistX = (info->posX - var->mapX) * var->deltaDistX;
	}
	else
	{
		var->stepX = 1;
		var->sideDistX = (var->mapX + 1 - info->posX) * var->deltaDistX;
	}
	if (var->rayDirY < 0)
	{
		var->stepY = -1;
		var->sideDistY = (info->posY - var->mapY) * var->deltaDistY;
	}
	else
	{
		var->stepY = 1;
		var->sideDistY = (var->mapY + 1 - info->posY) * var->deltaDistY;
	}
}

static void	set_side_merge_sideDist_deltaDist(t_var *var)
{
	if (var->sideDistX < var->sideDistY)
	{
		var->sideDistX += var->deltaDistX;
		var->mapX += var->stepX;
		var->side = 0;
	}
	else
	{
		var->sideDistY += var->deltaDistY;
		var->mapY += var->stepY;
		var->side = 1;
	}
}

static void	calc_perpWallDist_by_side_pos(t_hub *info, t_var *var)
{
	if (var->side == 0)
		var->perpWallDist = (var->mapX - info->posX + (1 - var->stepX) / 2) / var->rayDirX;
	else
		var->perpWallDist = (var->mapY - info->posY + (1 - var->stepY) / 2) / var->rayDirY;
}

static void	calc_drawstart_drawend_by_perpWallDist(t_hub *info, t_var *var)
{
	var->lineHeight = (int)(info->screenheight / var->perpWallDist);
	var->drawStart = (info->screenheight / 2) - (var->lineHeight / 2);
//	if (var->drawStart < 0)
//		var->drawStart = 0;
	var->drawEnd = (var->lineHeight / 2) + (info->screenheight / 2);
	if (var->drawEnd >= info->screenheight)
		var->drawEnd = info->screenheight /*- 1*/;
}

static void	set_default_var(t_hub *info, t_var *var)
{
	var->cameraX = 2 * var->x / (double)info->screenwide - 1;
	var->rayDirX = info->dirX + info->planeX * var->cameraX;
	var->rayDirY = info->dirY + info->planeY * var->cameraX;
	var->mapX = (int)info->posX;
	var->mapY = (int)info->posY;
	var->deltaDistX = fabs(1 / var->rayDirX);
	var->deltaDistY = fabs(1 / var->rayDirY);
	var->hit = 0;
}

int	dda(t_hub *info)
{
	t_var	var;

	var.x = 0;
	while (var.x < info->screenwide)
	{
		set_default_var(info, &var);
		stepX_sideDist_by_rayDir(info, &var);
		while (var.hit == 0)
		{
			set_side_merge_sideDist_deltaDist(&var);
			if (info->map[var.mapY][var.mapX] == '1')
				var.hit = 1;
			else if (info->map[var.mapY][var.mapX] == '2')
			{

			}
		}
		calc_perpWallDist_by_side_pos(info, &var);
		calc_drawstart_drawend_by_perpWallDist(info, &var);
		if (var.side == 0)
			var.wallX = info->posY + var.perpWallDist * var.rayDirY;
		else
			var.wallX = info->posX + var.perpWallDist * var.rayDirX;
		var.wallX -= floor(var.wallX);
		var.texX = (int)(var.wallX * (double)texWidth);
		if (var.side == 0 && var.rayDirX > 0)
			var.texNum = 3;
		else if (var.side == 0 && var.rayDirX < 0)
			var.texNum = 2;
		else if (var.side == 1 && var.rayDirY > 0)
			var.texNum = 1;
		else if (var.side == 1 && var.rayDirY < 0)
			var.texNum = 0;
		if (var.side == 0 && var.rayDirX < 0)
			var.texX = texWidth - var.texX - 1;
		if (var.side == 1 && var.rayDirY > 0)
			var.texX = texWidth - var.texX - 1;
		var.y = var.drawStart;
		if (var.drawStart < 0)
			var.y = 0;
		draw_hub(info, &var);
		var.x++;
	}
	return (0);
}

int	key_press(int key, t_hub *info)
{
	if (key == KEY_W)
	{
		if (info->map[(int)info->posY][(int)(info->posX + info->dirX * info->moveSpeed)] == '0')
			info->posX += info->dirX * info->moveSpeed;
		if (info->map[(int)(info->posY + info->dirY * info->moveSpeed)][(int)info->posX] == '0')
			info->posY += info->dirY * info->moveSpeed;
	}
	if (key == KEY_S)
	{
		if (info->map[(int)info->posY][(int)(info->posX - info->dirX * info->moveSpeed)] == '0')
			info->posX -= info->dirX * info->moveSpeed;
		if (info->map[(int)(info->posY - info->dirY * info->moveSpeed)][(int)info->posX] == '0')
			info->posY -= info->dirY * info->moveSpeed;
	}
	if (key == KEY_D)
	{
		double	oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotationSpeed) - info->dirY * sin(info->rotationSpeed);
		info->dirY = oldDirX * sin(info->rotationSpeed) + info->dirY * cos(info->rotationSpeed);
		double	oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotationSpeed) - info->planeY * sin(info->rotationSpeed);
		info->planeY = oldPlaneX * sin(info->rotationSpeed) + info->planeY * cos(info->rotationSpeed);
	}
	if (key == KEY_A)
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
