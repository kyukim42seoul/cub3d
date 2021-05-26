#include "cub3D.h"

static int	find_character(int map_height, char *line, t_character *c)
{
	static int	count;
	char	*temp;

	count = 0;
	temp = 0;
	if (ft_strchr(line, 'N'))
	{
		c->posX = (double)(ft_strlen(line) - ft_strlen(ft_strchr(line, 'N')) + 0.5);
		c->posY = (double)map_height + 0.5;
		c->dirX = 0;
		c->dirY = -1;
		c->planeX = 0.66;
		c->planeY = 0;
		temp = ft_strchr(line, 'N');
		*temp = '0';
		count++;
	}
	else if (ft_strchr(line,'S'))
	{
		c->posX = (double)(ft_strlen(line) - ft_strlen(ft_strchr(line, 'S')) + 0.5);
		c->posY = (double)map_height + 0.5;
		c->dirX = 0;
		c->dirY = 1;
		c->planeX = -0.66;
		c->planeY = 0;
		temp = ft_strchr(line, 'S');
		*temp = '0';
		count++;
	}
	else if (ft_strchr(line, 'W'))
	{
		c->posX = (double)(ft_strlen(line) - ft_strlen(ft_strchr(line, 'W')) + 0.5);
		c->posY = (double)map_height+ 0.5;
		c->dirX = -1;
		c->dirY = 0;
		c->planeX = 0;
		c->planeY = -0.66;
		temp = ft_strchr(line, 'W');
		*temp = '0';
		count++;
	}
	else if (ft_strchr(line, 'E'))
	{
		c->posX = (double)(ft_strlen(line) - ft_strlen(ft_strchr(line, 'E'))+ 0.5);
		c->posY = (double)map_height+ 0.5;
		c->dirX = 1;
		c->dirY = 0;
		c->planeX = 0;
		c->planeY = 0.66;
		temp = ft_strchr(line, 'E');
		*temp = '0';
		count++;
	}
	if (count > 1)
		error_function("Too many characters");
	return (count);
}
/*
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
*/
static void	find_sprite(t_hub *info, char *line, int map_height)
{
	int	index;
	t_sprite_list	*new;

	index = 0;
	if (info->sprite_list == NULL)
		info->sprite_list = new_sprite_node();
	while (line[index])
	{
		if (line[index] == '2')
		{
			new = new_sprite_node();
			new->x = index + 0.5;
			new->y = map_height + 0.5;
			new->distance = (info->c.posX - new->x) * (info->c.posX - new->x) + (info->c.posY - new->y) * (info->c.posY - new->y);
			add_back_sprite_node(info->sprite_list, new);
			info->number_of_sprite++;
		}
		index++;
	}
}

static char	*line_initialize(int len)
{
	char	*new_line;

	new_line = (char *)malloc(sizeof(char) * len + 1);
	if (!new_line)
		return (NULL);	// error check point
	ft_memset(new_line, ' ', len);
	new_line[len] = '\0';
	return (new_line);
}

void	parse_map(int fd, char ***map, t_hub *info)
{
	int	map_x;
	int	index;
	int	count;
	char	*line;
	char	*temp;
	t_list	*head;
	t_list	*current;
	t_list	*old;

	map_x = 0;
	index = 0;
	line = 0;
	count = 0;
	head = ft_lstnew(NULL);
	while (get_next_line(fd, &line) == 1 && info->error == 0)
	{
		if ((int)ft_strlen(line) > info->map_width)
			info->map_width = ft_strlen(line);
/*		if (head->next == NULL)
		{
			if (check_map_start(line) < 0)
			{
				info->error_message = ft_strdup("map_start_error\n");
				info->error++;
			}
		}
		*/
		temp = ft_strdup(line);
		count += find_character(info->map_height, temp, &info->c);
		current = ft_lstnew((void *)temp);
		if ((int)ft_strlen(current->content) > map_x)
			map_x = ft_strlen(current->content);
		info->map_height++;
		ft_lstadd_back(&head, current);
		free(line);
	}
	free(line);
	if (count != 1)
		return (error_function("Incollect_Character_Number"));
	*map = (char **)malloc(sizeof(char *) * (info->map_height + 1));
	current = head->next;
	free(head);
	while (current)
	{
		find_sprite(info, (char *)current->content, index);
		(*map)[index] = line_initialize(info->map_width);
		ft_memcpy((*map)[index], (char *)current->content, ft_strlen((char *)current->content));
		old = current;
		current = current->next;
		free(old->content);
		free(old);
		index++;
	}
	(*map)[index] = NULL;
	print_map((*map));
	check_boundary(info, (*map));
}



