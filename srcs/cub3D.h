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
# define X_EVENT_KEY_EXIT 17

typedef struct s_gdata
{
	int	x_render_size;
	int	y_render_size;
	char	*path_to_the_north_texture;
	char	*path_to_the_south_texture;
	char	*path_to_the_west_texture;
	char	*path_to_the_east_texture;
	char	*path_to_the_sprite_texture;
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
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_idata;

typedef struct info_hub
{
	t_gdata	*graphic;
	t_idata	image;
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
}	t_hub;

//cub_util.c
void	reset_info(t_hub *info);
void	print_structure(t_hub *info);
void	print_graphic(t_gdata *graphic_info);
void	verline (t_hub *info, int x, int y1, int y2, int color);
void	set_pixel_color(t_hub *info, int x, int y, int color);

//dda.c + 2 static verline, addr_pixel_put
int	dda(t_hub *info);
int	key_press(int key, t_hub *info);

//main.c + main + 1 static print_map

//parse_graphic.c + 3 static compare_text, free_by_count, cub_atoi
int	check_structure(t_gdata *graphic);
int	parse_cub(char *source_line, t_gdata *graphic);

//parse_map.c + 2 static find_character, check_map_start
void	parse_map(int fd, char ***map, t_hub *info);

//start_parsing.c
void	start_parsing(int fd, char ***map, t_hub *info);

#endif
