#include "cub3D.h"

int	main(int argc, char *argv[])
{
	t_info	*map_information;
	char	**map;
	char	*source_line;
	int		fd;

	fd = open("../conf.cub", O_RDONLY);
	map_information = malloc(sizeof(t_info));

	while (get_next_line(fd, &source_line) == 1)
	{
		if (*source_line != '\0')
		{
			parse_cub(source_line, map_information);
		}
	}

//	구조체 내용 확인용
	printf("x_render_size : %d\n", map_information->x_render_size);
	printf("y_render_size : %d\n", map_information->y_render_size);
	printf("path_to_the_north_texture : %s\n", map_information->path_to_the_north_texture);
	printf("path_to_the_south_texture : %s\n", map_information->path_to_the_south_texture);
	printf("path_to_the_west_texture : %s\n", map_information->path_to_the_west_texture);
	printf("path_to_the_east_texture : %s\n", map_information->path_to_the_east_texture);
	printf("path_to_the_sprite_texture : %s\n", map_information->path_to_the_sprite_texture);
	printf("f_red : %d\n", map_information->f_red);
	printf("f_green : %d\n", map_information->f_green);
	printf("f_blue : %d\n", map_information->f_blue);
	printf("c_red : %d\n", map_information->c_red);
	printf("c_green : %d\n", map_information->c_green);
	printf("c_blue : %d\n", map_information->c_blue);


	return (0);
}
