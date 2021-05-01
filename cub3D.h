#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "./Get_Next_Line/get_next_line.h"
#include "./Libft/libft.h"
#include "./mlx/mlx.h"

typedef struct dda_info
{
	int	*position;
	int	*direction;
	int	*plane;
}	tdda_info;

typedef struct	s_info
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
}	t_info;

//void	set_map_info(t_info *map_information);
int	parse_cub(char *source_line, t_info *map_information);
int	check_structure(t_info *map_information);
void	reset_map_information(t_info *map_information);
void	print_structure(t_info *map_information);
int	start_parsing(t_info *map_information, char **map);

#endif
