#include "cub3D.h"
/*
static void	sort_sprites(t_sprite *sprite, int *number_of_sprites)
{

}
*/
/*
static void	set_sprites_array(t_hub *info)
{
	int	index;

	index = 0;
	while (index < info->number_of_sprite)
	{
		info->sprite[index].distance = ((info->posX - info->sprite[index].x) * (info->posX - info->sprite[index].x)) + ((info->posY - info->sprite[index].y) * (info->posY - info->sprite[index].y));
		index++;
	}
}
*/
void	draw_sprite(t_hub *info)
{
//	int		index;
	int		sprite_screenX;
	int		sprite_height;
	int		draw_startY;
	int		draw_endY;
	int		draw_startX;
	int		draw_endX;
	int		sprite_width;
	int		stripe;
	int		texX;
	int		texY;
	int		y;
	int		d;
	int		color;
	double	spriteX;
	double	spriteY;
	double	invdet;
	double	transformX;
	double	transformY;
	t_sprite_list	*start;

	start = info->sprite_list->next;
//	index = 0;
//	set_sprites_array(info);
	while (start)
	{
		spriteX = start->x - info->posX;
		spriteY = start->y - info->posY;
		invdet = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY);
		transformX = invdet * (info->dirY * spriteX - info->dirX * spriteY);
		transformY = invdet * (-info->planeY * spriteX  + info->planeX * spriteY);
/*
		if (transformY < 0.05 && transformY >= 0)
			transformY = 0.01;
		else if (transformY > -0.05 && transformY < 0)
			transformY = -0.01;
*/
		sprite_screenX = (int)((info->graphic->x_render_size / 2) * (1 + transformX / transformY));
//		printf("%f %d\n", transformY, sprite_screenX);
		sprite_height = abs((int)(info->graphic->y_render_size / transformY)); //transformY 에 왜 괄호가 있을까? 구현 후 확인.
		draw_startY = -sprite_height / 2 + info->graphic->y_render_size / 2;
		if (draw_startY < 0)
			draw_startY = 0;
		draw_endY = sprite_height / 2 + info->graphic->y_render_size / 2;
		if (draw_endY >= info->graphic->y_render_size)
			draw_endY = info->graphic->y_render_size - 1;

		sprite_width = abs((int)(info->graphic->y_render_size / transformY));
		draw_startX = -sprite_width / 2 + sprite_screenX;
		if (draw_startX < 0)
			draw_startX = 0;
		draw_endX = sprite_width / 2 + sprite_screenX;
		if (draw_endX >= info->graphic->x_render_size)
			draw_endX = info->graphic->x_render_size - 1;

		stripe = draw_startX;
//-------------------------------------------------------up : set_var | down : draw_stripe
		while (stripe < draw_endX)
		{
			texX = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screenX)) * texWidth / sprite_width) / 256;
			if (transformY > 0 && stripe > 0 && stripe < info->graphic->x_render_size && transformY < info->z[stripe])
			{
				y = draw_startY;
				while (y < draw_endY)
				{
					d = y * 256 - info->graphic->y_render_size * 128 + sprite_height * 128; //256, 128 factors to avoid floats(??)
					texY = ((d * texHeight) / sprite_height) / 256;
					color = info->texture[4][texY * texWidth + texX];
					if ((color & 0x00FFFFFF) != 0)
						info->buf[y][stripe] = color;
					y++;
				}
			}
			stripe++;
		}
		start = start->next;
	}
}
