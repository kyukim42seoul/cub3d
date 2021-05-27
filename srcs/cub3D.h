/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 00:32:45 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/28 01:10:27 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17
# define TEXHEIGHT 64
# define TEXWIDTH 64
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "Get_Next_Line/get_next_line.h"
# include "libft/libft.h"
# include "mlx/mlx.h"

typedef struct	s_draw_element
{
	int		scr_x;
	int		sprt_h;
	int		start_y;
	int		end_y;
	int		start_x;
	int		end_x;
	int		sprt_width;
	int		x;
	int		tex_x;
	int		tex_y;
	int		y;
	int		d;
	int		color;
	double	sprt_x;
	double	sprt_y;
	double	invdet;
	double	trans_x;
	double	trans_y;
}				t_draw_element;
typedef struct	s_sprite_list
{
	double					x;
	double					y;
	double					distance;
	struct s_sprite_list	*prev;
	struct s_sprite_list	*next;
}				t_sprite_list;

typedef struct	s_key
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	esc;
}				t_key;

typedef struct	s_var
{
	int		x;
	int		map_x;
	int		map_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_h;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perpwalldist;
	int		color;
	int		drawstart;
	int		drawend;
	int		texnum;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	int		y;
	double	step;
	double	tex_pos;
}				t_var;

typedef struct	s_graphic
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*pathsprite;
	int		x_render_size;
	int		y_render_size;
	int		floor_color;
	int		ceiling_color;
}				t_graphic;

typedef struct	s_image
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		img_height;
	int		img_width;
}				t_image;

typedef struct	s_character
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	movspd;
	double	rotspd;
	int		cnt;
}				t_character;

typedef struct	s_info
{
	t_graphic		*g;
	t_image			img;
	t_sprite_list	*sprite_list;
	t_key			k;
	t_character		c;
	void			*mlx;
	void			*win;
	int				scrn_w;
	int				scrn_h;
	char			**map;
	int				**texture;
	int				**buf;
	double			*z;
	int				number_of_sprite;
	int				save;
	int				map_width;
	int				map_height;
}				t_info;
/*
**cub_util.c
*/
void			free_by_count(char **source, int count);
void			set_texture_buf(t_info *info);
void			set_screen_buf(t_info *info);
void			load_img(t_info *info, int *texture, char *path, t_image *img);
void			load_texture(t_info *info);
void			combine_color(int *color, int red, int green, int blue);
void			error_function(char *msg);
int				compare_text(char *source_line, char *text);
void			check_render_size(t_info *info);
/*
**dda.c + 5 static
*/
int				dda(t_info *info);
/*
**dda_util.c
*/
void			calc_perpwalldist_by_side_pos(t_character c, t_var *var);
void			calc_d_start_d_end_by_perpwalldist(t_info *info, t_var *var);
void			set_texnum_by_side_raydir(t_var *var);
void			calc_texx_by_side_raydir(t_var *var);
void			calc_wallx_by_side(t_info *info, t_var *var);
/*
**main.c
*/
int				main_loop(t_info *info);
void			set_sprite_distance(t_character c, t_sprite_list *node);
/*
**parse_graphic.c + 3 static compare_text, free_by_count, cub_atoi
*/
int				check_structure(t_graphic *g);
void			parse_cub(char *source_line, t_graphic *g);
/*
**parse_map.c + 2 static find_character, check_map_start
*/
void			parse_map(int fd, char ***map, t_info *info);
int				check_char(char c, char *vaild);
/*
**start_parsing.c
*/
void			start_parsing(int fd, char ***map, t_info *info);
/*
**draw.c
*/
void			draw_wall(t_info *info, t_var *var);
void			draw_background(t_info *info, t_var *var);
void			draw_image(t_info *info);
/*
**sprite.c
*/
void			draw_sprite(t_info *info);
void			set_sprite_distance(t_character c, t_sprite_list *node);
/*
**key.c
*/
int				key_update(t_info *info);
int				key_press(int key, t_info *info);
int				key_release(int key, t_info *info);
/*
**handle_list.c + 5 static
*/
void			sort_sprite_node(t_sprite_list *start);
void			add_node(t_sprite_list *list, t_sprite_list *new);
t_sprite_list	*new_sprite_node(void);
/*
**bitmap.c + 3 static
*/
void			make_bitmap(char **argv, t_info *info);
/*
**map_efficiency.c
*/
void			check_boundary(t_info *info, char **map);
/*
**reset_info.c
*/
void			reset_info(t_info *info);
/*
**sort.c
*/
int				scan_forward(t_sprite_list **start);
int				scan_backward(t_sprite_list *head, t_sprite_list **tail);
/*
**find_character.c
*/
void			find_character(int map_height, char *line, t_character *c);

#endif
