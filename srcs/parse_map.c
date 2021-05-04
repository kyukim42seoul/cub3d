#include "cub3D.h"

void	parse_map(int fd, char ***map)
{
	int	map_x;
	int	map_y;
	int	index;
	char	*line;
	t_list	*head;
	t_list	*current;

	map_x = 0;
	map_y = 0;
	index = 0;
	line = 0;
	head = ft_lstnew(NULL);
	while (get_next_line(fd, &line) == 1)
	{
		current = ft_lstnew((void *)line);
		if ((int)ft_strlen(current->content) > map_x)
			map_x = ft_strlen(current->content);
		map_y++;
		ft_lstadd_back(&head, current);
	}
	*map = (char **)malloc(sizeof(char *) * (map_y + 1));
	current = head->next;
	while (current->next)
	{
		(*map)[index] = ft_strdup((char *)current->content);
		current = current->next;
		index++;
	}
}

/*
void	find_pos(char **map, tdda_info *vector)
{
	char	**temp;
	int	x;
	int	y;

	temp = 0;
	x = 0;
	y = 0;
	while (!temp && map[y])
	{
		if (ft_strchr(map[y], 'N'))
		{
			vector->pos->x ==
			vector->dir->x == 0;
			vector->dir->y == 1;
		}
		else if (ft_strchr(map[y],'S'))
		{
			vector->dir->x == 0;
			vector->dir->y == -1;
		}
		else if (ft_strchr(map[y], 'W'))
		{
			vector->dir->x == -1;
			vector->dir->y == 0;
		}
		else if (ft_strchr(map[y], 'E'))
		{
			vector->dir->x == 1;
			vector->dir->y == 0;
		}
		y++;
	}
}
*/
