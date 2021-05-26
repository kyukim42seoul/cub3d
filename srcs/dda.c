#include "cub3D.h"

static	void	stepX_sideDist_by_rayDir(t_character c, t_var *var)
{
	if (var->rayDirX < 0)
	{
		var->stepX = -1;
		var->sideDistX = (c.posX - var->mapX) * var->deltaDistX;
	}
	else
	{
		var->stepX = 1;
		var->sideDistX = (var->mapX + 1 - c.posX) * var->deltaDistX;
	}
	if (var->rayDirY < 0)
	{
		var->stepY = -1;
		var->sideDistY = (c.posY - var->mapY) * var->deltaDistY;
	}
	else
	{
		var->stepY = 1;
		var->sideDistY = (var->mapY + 1 - c.posY) * var->deltaDistY;
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

static void	calc_perpWallDist_by_side_pos(t_character c, t_var *var)
{
	if (var->side == 0)
		var->perpWallDist = (var->mapX - c.posX + (1 - var->stepX) / 2) / var->rayDirX;
	else
		var->perpWallDist = (var->mapY - c.posY + (1 - var->stepY) / 2) / var->rayDirY;
}

static void	calc_drawstart_drawend_by_perpWallDist(t_hub *info, t_var *var)
{
	var->lineHeight = (int)(info->screenheight / var->perpWallDist);
	var->drawStart = (info->screenheight / 2) - (var->lineHeight / 2);
	var->drawEnd = (var->lineHeight / 2) + (info->screenheight / 2);
	if (var->drawEnd >= info->screenheight)
		var->drawEnd = info->screenheight;
}

static void	set_default_var(t_hub *info, t_var *var)
{
	var->cameraX = 2 * var->x / (double)info->screenwidth - 1;
	var->rayDirX = info->c.dirX + info->c.planeX * var->cameraX;
	var->rayDirY = info->c.dirY + info->c.planeY * var->cameraX;
	var->mapX = (int)info->c.posX;
	var->mapY = (int)info->c.posY;
	var->deltaDistX = fabs(1 / var->rayDirX);
	var->deltaDistY = fabs(1 / var->rayDirY);
	var->hit = 0;
}

int	dda(t_hub *info)
{
	t_var	var;

	var.x = 0;
	while (var.x < info->screenwidth)
	{
		set_default_var(info, &var);
		stepX_sideDist_by_rayDir(info->c, &var);
		while (var.hit == 0)
		{
			set_side_merge_sideDist_deltaDist(&var);
			if (info->map[var.mapY][var.mapX] == '1')
				var.hit = 1;
		}
		calc_perpWallDist_by_side_pos(info->c, &var);
		info->z[var.x] = var.perpWallDist;
		calc_drawstart_drawend_by_perpWallDist(info, &var);
		if (var.side == 0)
			var.wallX = info->c.posY + var.perpWallDist * var.rayDirY;
		else
			var.wallX = info->c.posX + var.perpWallDist * var.rayDirX;
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
		draw_background(info, &var);
		draw_wall(info, &var);
		var.x++;
	}
	return (0);
}
