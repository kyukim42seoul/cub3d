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

typedef struct graphic_info
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
}	g_info;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct info_hub
{
	g_info	*graphic;
	t_data	image;
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


int	parse_cub(char *source_line, g_info *graphic);
int	check_structure(g_info *graphic);
void	reset_info(t_hub *info);
void	start_parsing(int fd, char ***map, t_hub *info);
void	parse_map(int fd, char ***map, t_hub *info);
int	dda(t_hub *info);
int	key_press(int key, t_hub *info);
void	print_structure(t_hub *info);
void	print_graphic(g_info *graphic_info);

#endif
