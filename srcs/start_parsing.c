#include "cub3D.h"


void	start_parsing(int fd, char ***map, g_info *graphic_info)
{
	int	count;
	char	*line;

	count = 0;
	while (count != 13)
	{
		count = check_structure(graphic_info);
		get_next_line(fd, &line);
		if (*line != '\0')
			parse_cub(line, graphic_info);
	}
	parse_map(fd, map);
}
