#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "Get_Next_Line/get_next_line.h"
#include "libft/libft.h"
#include "mlx/mlx.h"

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

# define KEY_ESC 53

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17

# define texHeight 64
# define texWidth 64

typedef struct s_sprite_list
{
	int						number;
	int						spriteX;
	int						spriteY;
	double					distance;
	struct s_sprite_list	*next;
}	t_sprite_list;

typedef struct s_flag
{
	int	key_w;
	int	key_s;
	int	key_a;
	int	key_d;
	int	key_esc;
}	t_flag;
typedef struct s_var
{
	int	x;
	int	mapX;
	int	mapY;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int	stepX;
	int	stepY;
	int	hit;
	int	side;
	int	lineHeight;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int	color;
	int	drawStart;
	int	drawEnd;
	int	texNum;
	double	wallX;
	int	texX;
	int	texY;
	int y;
	double	step;
	double	texPos;
}	t_var;

typedef struct s_gdata
{
	int	x_render_size;
	int	y_render_size;
	char	*path_to_the_north_texture;
	char	*path_to_the_south_texture;
	char	*path_to_the_west_texture;
	char	*path_to_the_east_texture;
	char	*path_to_the_sprite_texture;
	char	*path_to_the_sky_texture;
	char	*path_to_the_floor_texture;
	int	f_red;
	int	f_green;
	int	f_blue;
	int	c_red;
	int	c_green;
	int	c_blue;
}	t_gdata;

typedef struct s_idata
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_height;
	int		img_width;
}	t_idata;

typedef struct s_sprite
{
	int	order;
	double	x;
	double	y;
	double	distance;
}	t_sprite;

typedef struct info_hub
{
	t_gdata	*graphic;
	t_idata	image;
	t_sprite	*sprite;
	t_flag	flag;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	moveSpeed;
	double	rotationSpeed;
	int	error;
	char	*error_message;
	void	*mlx;
	void	*win;
	int		screenwide;
	int		screenheight;
	char	**map;
	int	**texture;
	int	**buf;
	double	*z;
	int	number_of_sprite;
}	t_hub;

//cub_util.c
void	reset_info(t_hub *info);
void	print_structure(t_hub *info);
void	print_graphic(t_gdata *graphic_info);
void	set_pixel_color(t_hub *info, int x, int y, int color);
void	set_texture_buf(t_hub *info);
void	set_screen_buf(t_hub *info);
void	draw_image(t_hub *info);
void	load_image(t_hub *info, int *texture, char *path, t_idata *image);
void	load_texture(t_hub *info);

//dda.c + 5 static
int	dda(t_hub *info);

//main.c + main + 1 static print_map
int	main_loop(t_hub *info);

//parse_graphic.c + 3 static compare_text, free_by_count, cub_atoi
int	check_structure(t_gdata *graphic);
int	parse_cub(char *source_line, t_gdata *graphic);

//parse_map.c + 2 static find_character, check_map_start
void	parse_map(int fd, char ***map, t_hub *info);

//start_parsing.c
void	start_parsing(int fd, char ***map, t_hub *info);

//draw.c
void	draw_hub(t_hub *info, t_var *var);

//sprite.c
void	draw_sprite(t_hub *info);

//key.c
int	key_update(t_hub *info);
int	key_press(int key, t_hub *info);
int	key_release(int key, t_hub *info);


#endif
