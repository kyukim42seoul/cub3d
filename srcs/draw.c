#include "cub3D.h"

static void	draw_background(t_hub *info, t_var *var)
{
	int	eyesight = info->screenheight / 2;
	int	sky_color = 0x0000FF66;
	int	floor_color = 0x00FF8800;
	int	y;

	y = 0;
	while (y < eyesight)
	{
		info->buf[y][var->x] = sky_color;
		y++;
	}
	while (y < info->screenheight)
	{
		info->buf[y][var->x] = floor_color;
		y++;
	}
}

static void	draw_wall(t_hub *info, t_var *var)
{
	while (var->y < var->drawEnd)
	{
		//var->texY = (int)var->texPos & (texHeight - 1); // ㄷㄷ 이거 뭐야 & 은 뭐고... texHeight 에서 1은 또 왜 빼는데;;
		var->texY = (double)(var->y - var->drawStart) / var->lineHeight * 63;
//		var->texPos += var->step;
		var->color = info->texture[var->texNum][texHeight * var->texY + var->texX];
//		if (var->side == 1)
//			var->color = (var->color >> 1) & 8355711;
		info->buf[var->y][var->x] = var->color;
		var->y++;
	}
}

void	draw_hub(t_hub *info, t_var *var)
{
	draw_background(info, var);
	draw_wall(info, var);
}
