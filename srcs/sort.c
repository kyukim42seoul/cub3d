/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:42:13 by kyukim            #+#    #+#             */
/*   Updated: 2021/05/27 17:38:54 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	int				compare(t_sprite_list *left, t_sprite_list *right)
{
	if (!left || !right)
		return (0);
	if (left->distance < right->distance)
		return (1);
	else
		return (0);
}

static t_sprite_list	*swap(t_sprite_list *left, t_sprite_list *right)
{
	left->next = right->next;
	if (right->next)
		right->next->prev = left;
	right->next = left;
	right->prev = left->prev;
	left->prev->next = right;
	left->prev = right;
	return (right);
}

int						scan_forward(t_sprite_list **start)
{
	int	check;

	check = 0;
	while ((*start)->next)
	{
		if (compare(*start, (*start)->next))
		{
			*start = swap(*start, (*start)->next);
			check++;
		}
		*start = (*start)->next;
	}
	return (check);
}

int						scan_backward(t_sprite_list *head, t_sprite_list **tail)
{
	int	check;

	check = 0;
	while ((*tail)->prev != head)
	{
		if (compare((*tail)->prev, *tail))
		{
			*tail = swap((*tail)->prev, *tail)->next;
			check++;
		}
		*tail = (*tail)->prev;
	}
	return (check);
}

void					sort_sprite_node(t_sprite_list *start)
{
	int				compare_count;
	t_sprite_list	*head;

	compare_count = -1;
	head = start->prev;
	while (compare_count != 0)
	{
		compare_count = scan_forward(&start);
		compare_count = scan_backward(head, &start);
	}
}
