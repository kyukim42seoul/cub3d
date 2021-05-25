#include "cub3D.h"

void	draw_image(t_hub *info)
{
	int	y;
	int	x;

	y = 0;
	while (y < info->screenheight)
	{
		x = 0;
		while (x < info->screenwide)
		{
			info->image.addr[y * info->image.line_length / 4 + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_sync(1, info->image.img);
	mlx_put_image_to_window(info->mlx, info->win, info->image.img, 0, 0);
	mlx_sync(3, info->win);
}

void	draw_background(t_hub *info, t_var *var)
{
	int	eyesight = info->screenheight / 2;
	int	y;

	y = 0;
	while (y < eyesight)
	{
		info->buf[y][var->x] = info->graphic->ceiling_color;
		y++;
	}
	while (y < info->screenheight)
	{
		info->buf[y][var->x] = info->graphic->floor_color;
		y++;
	}
}

void	draw_wall(t_hub *info, t_var *var)
{
	while (var->y < var->drawEnd)
	{
		//var->texY = (int)var->texPos & (texHeight - 1); // ㄷㄷ 이거 뭐야 & 은 뭐고... texHeight 에서 1은 또 왜 빼는데;;
		var->texY = (double)(var->y - var->drawStart) / var->lineHeight * 63;
//		var->texPos += var->step;
		var->color = info->texture[var->texNum][texHeight * var->texY + var->texX];
		if (var->side == 1)
			var->color = (var->color >> 1) & 8355711;
		info->buf[var->y][var->x] = var->color;
		var->y++;
	}
}
