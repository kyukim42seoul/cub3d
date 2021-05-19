#include "cub3D.h"


void	start_parsing(int fd, char ***map, t_hub *info)
{
	int	count;
	char	*line;

	count = 0;
	while (count != 13)
	{
		count = check_structure(info->graphic); //ok
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
