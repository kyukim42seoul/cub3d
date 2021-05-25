#include "cub3D.h"

static int	complete_structure(t_gdata *graphic)
{
	if (!graphic->path_to_the_north_texture)
		return (0);
	else if (!graphic->path_to_the_south_texture)
		return (0);
	else if (!graphic->path_to_the_west_texture)
		return (0);
	else if (!graphic->path_to_the_east_texture)
		return (0);
	else if (!graphic->path_to_the_sprite_texture)
		return (0);
	else if (!graphic->x_render_size)
		return (0);
	else if (!graphic->y_render_size)
		return (0);
	else if (graphic->floor_color == -1)
		return (0);
	else if (graphic->ceiling_color == -1)
		return (0);
	else
		return (1);
}

void	start_parsing(int fd, char ***map, t_hub *info)
{
	int	count;
	char	*line;

	count = 0;
	while (!complete_structure(info->graphic))
	{
		get_next_line(fd, &line);
		if (*line != '\0')
		{
			parse_cub(line, info->graphic); //ok free by counts 갯수와 인덱스를 보니 잘 free 되는 것 같음
			free(line);
		}
		else
			free(line);
	}
	parse_map(fd, map, info);
}
