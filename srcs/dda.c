#include "cub3D.h"

int	main_loop(t_hub *info)
{
	dda(info);
	mlx_put_image_to_window(info->mlx, info->win, info->image.img, 0, 0);
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
	if (var->drawStart < 0)
		var->drawStart = 0;
	var->drawEnd = (var->lineHeight / 2) + (info->screenheight / 2);
	if (var->drawEnd >= info->screenheight)
		var->drawEnd = info->screenheight - 1;
}

static void	set_color_by_map_value(t_hub *info, t_var *var)
{
	if (info->map[var->mapY][var->mapX] == '1')
		var->color = 0xFF0000;
	else
		var->color = 0x123145;
	if (var->side == 1)
		var->color = var->color / 2;
}

int	dda(t_hub *info)
{
	t_var	var;

	var.x = 0;
	while (var.x < info->screenwide)
	{
		var.cameraX = 2 * var.x / (double)info->screenwide - 1;
		var.rayDirX = info->dirX + info->planeX * var.cameraX;
		var.rayDirY = info->dirY + info->planeY * var.cameraX;

		var.mapX = (int)info->posX;
		var.mapY = (int)info->posY;

		var.deltaDistX = fabs(1 / var.rayDirX);
		var.deltaDistY = fabs(1 / var.rayDirY);

		var.hit = 0;
		stepX_sideDist_by_rayDir(info, &var);
		while (var.hit == 0)
		{
			set_side_merge_sideDist_deltaDist(&var);
			if (info->map[var.mapY][var.mapX] == '1')
				var.hit = 1;
		}
		calc_perpWallDist_by_side_pos(info, &var);
		calc_drawstart_drawend_by_perpWallDist(info, &var);
//		set_color_by_map_value(info, &var);
//		verline(info, var.x, var.drawStart, var.drawEnd, var.color);
		var.texNum = info->map[var.mapX][var.mapY] - 1; // -1 은 뭐며, mapX 랑 mapY 위치는 또 왜 반대인가??

		if (var.side == 0)
			var.wallX = info->posY + var.perpWallDist * var.rayDirY;
		else
			var.wallX = info->posX + var.perpWallDist * var.rayDirX;
		var.wallX -= floor(var.wallX);

		var.texX = (int)(var.wallX * (double)texWidth);
		if (var.side == 0 && var.rayDirX > 0) // 동쪽으로 추측
			var.texX = texWidth - var.texX -1;
		if (var.side == 1 && var.rayDirY < 0) // 북쪽으로 추측
			var.texX = texWidth - var.texX - 1;

		var.step = 1.0 * texHeight / var.lineHeight; // 텍스쳐 높이를 그려야 할 선 길이로 나눈 건 이해가 되는데 1을 곱하는 이유는?
		var.texPos = (var.drawStart - info->screenheight / 2 + info->screenheight / 2) * var.step;
		var.y = var.drawStart;
		while (var.y < var.drawEnd)
		{
			var.texY = (int)var.texPos & (texHeight - 1); // ㄷㄷ 이거 뭐야 & 은 뭐고... texHeight 에서 1은 또 왜 빼는데;;
			var.texPos += var.step;
			var.color = info->texture[var.texNum][texHeight * var.texY + var.texX];
			if (var.side == 1)
				var.color = (var.color >> 1) & 8355711;
			info->buf[var.y][var.x] = var.color;
		}
		var.x++;
	}
	return (0);
}

int	key_press(int key, t_hub *info)
{
//	printf("%s\n", info->map[(int)info->posY]);
//	printf("%d %d %c\n", (int)(info->posX + info->dirX * info->moveSpeed), (int)info->posY, info->map[(int)info->posY][(int)(info->posX + info->dirX * info->moveSpeed)]);
//	printf("%d %d %c\n", (int)(info->posX), (int)info->posY, info->map[(int)info->posY][(int)(info->posX)]);
	if (key == KEY_W)
	{
		printf("W\n");
		if (info->map[(int)info->posY][(int)(info->posX + info->dirX * info->moveSpeed)] == '0')
		{
//			printf("Wx\n");
			info->posX += info->dirX * info->moveSpeed;
		}
		if (info->map[(int)(info->posY + info->dirY * info->moveSpeed)][(int)info->posX] == '0')
		{
//			printf("Wy\n");
			info->posY += info->dirY * info->moveSpeed;
		}
	}
	if (key == KEY_S)
	{
		printf("S\n");
		if (info->map[(int)info->posY][(int)(info->posX - info->dirX * info->moveSpeed)] == '0')
		{
//			printf("Sx\n");
			info->posX -= info->dirX * info->moveSpeed;
		}
		if (info->map[(int)(info->posY - info->dirY * info->moveSpeed)][(int)info->posX] == '0')
		{
//			printf("Sy\n");
			info->posY -= info->dirY * info->moveSpeed;
		}
	}
	if (key == KEY_D)
	{
		printf("D\n");
		double	oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotationSpeed) - info->dirY * sin(info->rotationSpeed);
		info->dirY = oldDirX * sin(info->rotationSpeed) + info->dirY * cos(info->rotationSpeed);
		double	oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotationSpeed) - info->planeY * sin(info->rotationSpeed);
		info->planeY = oldPlaneX * sin(info->rotationSpeed) + info->planeY * cos(info->rotationSpeed);
	}
	if (key == KEY_A)
	{
		printf("A\n");
		double	oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotationSpeed) - info->dirY * sin(-info->rotationSpeed);
		info->dirY = oldDirX * sin(-info->rotationSpeed) + info->dirY * cos(-info->rotationSpeed);
		double	oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotationSpeed) - info->planeY * sin(-info->rotationSpeed);
		info->planeY = oldPlaneX * sin(-info->rotationSpeed) + info->planeY * cos(-info->rotationSpeed);
	}
//	printf("%f %f\n", info->dirX, info->dirY);
	if (key == KEY_ESC)
		exit(0);
	return (0);
}
