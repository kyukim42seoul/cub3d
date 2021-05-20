#include "cub3D.h"

static int	find_character(int map_y, char *line, t_hub *info)
{
	static int	count;
	char	*temp;

	count = 0;
	temp = 0;
	if (ft_strchr(line, 'N'))
	{
		info->posX = (double)(ft_strlen(line) - ft_strlen(ft_strchr(line, 'N')) + 0.5);
		info->posY = (double)map_y + 0.5;
		info->dirX = 0;
		info->dirY = -1;
		info->planeX = 0.66;
		info->planeY = 0;
		temp = ft_strchr(line, 'N');
		*temp = '0';
		count++;
	}
	else if (ft_strchr(line,'S'))
	{
		info->posX = (double)(ft_strlen(line) - ft_strlen(ft_strchr(line, 'S')) + 0.5);
		info->posY = (double)map_y + 0.5;
		info->dirX = 0;
		info->dirY = 1;
		info->planeX = -0.66;
		info->planeY = 0;
		temp = ft_strchr(line, 'S');
		*temp = '0';
		count++;
	}
	else if (ft_strchr(line, 'W'))
	{
		info->posX = (double)(ft_strlen(line) - ft_strlen(ft_strchr(line, 'W')) + 0.5);
		info->posY = (double)map_y+ 0.5;
		info->dirX = -1;
		info->dirY = 0;
		info->planeX = 0;
		info->planeY = -0.66;
		temp = ft_strchr(line, 'W');
		*temp = '0';
		count++;
	}
	else if (ft_strchr(line, 'E'))
	{
		info->posX = (double)(ft_strlen(line) - ft_strlen(ft_strchr(line, 'E'))+ 0.5);
		info->posY = (double)map_y+ 0.5;
		info->dirX = 1;
		info->dirY = 0;
		info->planeX = 0;
		info->planeY = 0.66;
		temp = ft_strchr(line, 'E');
		*temp = '0';
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

static void	find_sprite(t_hub *info, char *line, int map_y)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == '2')
		{
			info->sprite[info->number_of_sprite].x = index + 0.5;
			info->sprite[info->number_of_sprite].y = map_y + 0.5;
			info->number_of_sprite++;
		}
		index++;
	}
}

void	parse_map(int fd, char ***map, t_hub *info)
{
	int	map_x;
	int	map_y;
	int	index;
	int	count;
	char	*line;
	char	*temp;
	t_list	*head;
	t_list	*current;
	t_list	*old;

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
		temp = ft_strdup(line);
		count += find_character(map_y, temp, info);
		find_sprite(info, line, map_y);
//--------------------

//--------------------
		current = ft_lstnew((void *)temp);
		if ((int)ft_strlen(current->content) > map_x)
			map_x = ft_strlen(current->content);
		map_y++;
		ft_lstadd_back(&head, current);
		free(line);
	}
	free(line);
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
		free(head);
		while (current->next)
		{
			(*map)[index] = ft_strdup((char *)current->content);
			old = current;
			current = current->next;
			free(old->content);
			free(old);
			index++;
		}
		(*map)[index] = NULL;
	}
}



