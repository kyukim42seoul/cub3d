#include "cub3D.h"

t_sprite_list	*find_start(t_sprite_list *cur) // 결과 확인용으로만 쓰고 나중에 지울 것
{
	while (cur->prev)
		cur = cur->prev;
	return (cur->next);
}

void	print_sprite_list(t_sprite_list *start) // 결과 확인용으로만 쓰고 나중에 지울 것
{
	while (start->next)
	{
		printf("x y dist : %.2f %.2f %.2f\n", start->x, start->y, start->distance);
		start = start->next;
	}
	printf("x y dist : %.2f %.2f %.2f\n", start->x, start->y, start->distance);
}

static t_sprite_list	*last_sprite_node(t_sprite_list *node)
{
	while (node->next)
		node = node->next;
	return (node);
}

static	int	compare(t_sprite_list *left, t_sprite_list *right)
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

static int	scan_forward(t_sprite_list **start)
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

static int	scan_backward(t_sprite_list *head, t_sprite_list **tail)
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

void	sort_sprite_node(t_sprite_list *start)
{
	int	compare_count;
	t_sprite_list	*head;

	compare_count = -1;
	head = start->prev;
	while (compare_count != 0)
	{
		compare_count = scan_forward(&start);
		compare_count = scan_backward(head, &start);
	}
}

void	add_back_sprite_node(t_sprite_list *list, t_sprite_list *new)
{
	list = last_sprite_node(list);
	list->next = new;
	new ->prev = list;
}

t_sprite_list	*new_sprite_node(void)
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