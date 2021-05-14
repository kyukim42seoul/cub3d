#ifndef TEST_CUB3D_H
# define TEST_CUB3D_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "srcs/Get_Next_Line/get_next_line.h"
#include "srcs/libft/libft.h"
#include "srcs/mlx/mlx.h"

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

# define KEY_ESC 53

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_EXIT 17

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_info
{
	t_img	*img;
	void	*mlx;
	void	*win;
}	t_info;



#endif
