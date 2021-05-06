#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "Get_Next_Line/get_next_line.h"
#include "libft/libft.h"
#include "mlx/mlx.h"

typedef struct vector
{
	double x;
	double y;
}	v_info;

typedef struct dda_info
{
	v_info	*pos;
	v_info	*dir;
	v_info	*rayDir;
	v_info	*plane;
	v_info	*sideDist;
	v_info	*deltaDist;
//	double	*cameraX;
//	double	*perpWall;
}	tdda_info;

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

typedef struct info_hub
{
	g_info	*graphic;
	tdda_info	*vector;
	int	error;
	char	*error_message;
}	t_hub;

int	parse_cub(char *source_line, g_info *graphic);
int	check_structure(g_info *graphic);
void	reset_info(t_hub *info);
void	start_parsing(int fd, char ***map, t_hub *info);
void	parse_map(int fd, char ***map, t_hub *info);
int	dda(char **map, t_hub *info);

#endif
