#include "cub3D.h"

static int	find_character(int map_y, char *line, t_hub *info)
{
	static int	count;

	count = 0;
	if (ft_strchr(line, 'N'))
	{
		info->vector->pos->x = (double)(ft_strlen(line) - ft_strlen(ft_strchr(line, 'N')));
		info->vector->pos->y = (double)map_y;
		info->vector->dir->x = 0;
		info->vector->dir->y = 1;
		count++;
	}
	else if (ft_strchr(line,'S'))
	{
		info->vector->pos->x = (double)(ft_strlen(line) - ft_strlen(ft_strchr(line, 'S')));
		info->vector->pos->y = (double)map_y;
		info->vector->dir->x = 0;
		info->vector->dir->y = -1;
		count++;
	}
	else if (ft_strchr(line, 'W'))
	{
		info->vector->pos->x = (double)(ft_strlen(line) - ft_strlen(ft_strchr(line, 'W')));
		info->vector->pos->y = (double)map_y;
		info->vector->dir->x = -1;
		info->vector->dir->y = 0;
		count++;
	}
	else if (ft_strchr(line, 'E'))
	{
		info->vector->pos->x = (double)(ft_strlen(line) - ft_strlen(ft_strchr(line, 'E')));
		info->vector->pos->y = (double)map_y;
		info->vector->dir->x = 1;
		info->vector->dir->y = 0;
		count++;
	}
	if (count > 1)
	{
		info->error++;
		info->error_message = ft_strdup("Too many characters\n");
	}
	return (count);
}

static int	check_map_start(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == ' ' || line[index] == '1')
			index++;
		else
			return (-1);
	}
	return (0);
}

void	parse_map(int fd, char ***map, t_hub *info)
{
	int	map_x;
	int	map_y;
	int	index;
	int	count;
	char	*line;
	t_list	*head;
	t_list	*current;

	map_x = 0;
	map_y = 0;
	index = 0;
	line = 0;
	count = 0;
	head = ft_lstnew(NULL);
	while (get_next_line(fd, &line) == 1 && info->error == 0)
	{
		if (head->next == NULL)
		{
			if (check_map_start(line) < 0)
			{
				info->error_message = ft_strdup("map_start_error\n");
				info->error++;
			}
		}
		count += find_character(map_y, line, info);
		current = ft_lstnew((void *)line);
		if ((int)ft_strlen(current->content) > map_x)
			map_x = ft_strlen(current->content);
		map_y++;
		ft_lstadd_back(&head, current);
	}
	if (count != 1)
	{
		info->error++;
		info->error_message = ft_strdup("Incorrect character number\n");
		printf("count : %d\n", count);
	}
	if (info->error == 0)
	{
		*map = (char **)malloc(sizeof(char *) * (map_y + 1));
		current = head->next;
		while (current->next)
		{
			(*map)[index] = ft_strdup((char *)current->content);
			current = current->next;
			index++;
		}
	}
}



