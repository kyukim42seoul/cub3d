/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:32:35 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/27 17:41:35 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_sprite_list	*last_sprite_node(t_sprite_list *node)
{
	while (node->next)
		node = node->next;
	return (node);
}

void					add_node(t_sprite_list *list, t_sprite_list *new)
{
	list = last_sprite_node(list);
	list->next = new;
	new->prev = list;
}

t_sprite_list			*new_sprite_node(void)
{
	t_sprite_list	*new;

	new = (t_sprite_list *)malloc(sizeof(t_sprite_list));
	if (!new)
		return (NULL);
	new->y = 0;
	new->x = 0;
	new->distance = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
