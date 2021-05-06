#include "cub3D.h"


void	start_parsing(int fd, char ***map, t_hub *info)
{
	int	count;
	char	*line;

	count = 0;
	while (count != 13)
	{
		count = check_structure(info->graphic);
		get_next_line(fd, &line);
		if (*line != '\0')
			parse_cub(line, info->graphic);
	}
	parse_map(fd, map, info);
}
