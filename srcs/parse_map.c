/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:49 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/27 23:53:49 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void		find_sprite(t_hub *info, char *line, int map_height)
{
	int				index;
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
			new->distance = (info->c.posX - new->x) * (info->c.posX - new->x)\
			+ (info->c.posY - new->y) * (info->c.posY - new->y);
			add_node(info->sprite_list, new);
			info->number_of_sprite++;
		}
		index++;
	}
}

static char		*line_initialize(int len)
{
	char	*new_line;

	new_line = (char *)malloc(sizeof(char) * len + 1);
	if (!new_line)
		error_function("Fail Malloc line_initialize");
	ft_memset(new_line, ' ', len);
	new_line[len] = '\0';
	return (new_line);
}

static void		take_map_on_list(int fd, t_hub *info, t_list *head)
{
	char	*buf;
	char	*line;
	t_list	*current;

	buf = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (!line)
			error_function("Fail get_next_ilne");
		if ((int)ft_strlen(line) > info->map_width)
			info->map_width = ft_strlen(line);
		find_character(info->map_height, line, &info->c);
		buf = ft_strdup(line);
		current = ft_lstnew((void *)buf);
		ft_lstadd_back(&head, current);
		info->map_height++;
		free(line);
	}
	free(line);
	if (info->c.cnt != 1)
		return (error_function("Incollect Character Number"));
}

int				check_char(char c, char *vaild)
{
	int		index;

	index = 0;
	while (vaild[index])
	{
		if (vaild[index] == c)
			return (1);
		index++;
	}
	return (0);
}

void			parse_map(int fd, char ***map, t_hub *info)
{
	int		index;
	t_list	*head;
	t_list	*current;
	t_list	*old;

	index = 0;
	head = ft_lstnew(NULL);
	take_map_on_list(fd, info, head);
	*map = (char **)malloc(sizeof(char *) * (info->map_height + 1));
	current = head->next;
	free(head);
	while (current)
	{
		find_sprite(info, (char *)current->content, index);
		(*map)[index] = line_initialize(info->map_width);
		ft_memcpy((*map)[index], (char *)current->content,\
		ft_strlen((char *)current->content));
		old = current;
		free(old->content);
		free(old);
		current = current->next;
		index++;
	}
	(*map)[index] = NULL;
	check_boundary(info, (*map));
}
