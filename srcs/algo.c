/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:54:37 by theo              #+#    #+#             */
/*   Updated: 2025/11/10 18:16:48 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_bigger(t_node *head)
{
	int	value;

	value = head->value;
	while (head)
	{
		if (head->value > value)
			value = head->value;
		head = head->next;
	}
	return (value);
}
static int	find_dir(t_node *head, int value)
{
	int	size;
	int	index;

	size = count_list(head);
	index = 0;
	while (head)
	{
		if (head->value == value)
		{
			if (index > (size / 2))
				return (1);
			else
				return (-1);
		}
		index ++;
		head = head->next;
	}
	return (value);
}

static int	*find_smallests(t_node *head, int size)
{
	t_node	*tmp;
	int		*ptr;
	int		value;
	int		index;

	index = 0;
	ptr = malloc(sizeof(int) * size);
	if (!ptr)
		return (0);
	tmp = head;
	while (index < size)
	{
		value = head->value;
		while (head)
		{
			if (head->value < value && !is_in_chunk(ptr, head->value, index))
				value = head->value;
			head = head->next;
		}
		head = tmp;
		ptr[index] = value;
		index ++;
	}
	return (ptr);
}

void	push_all_to_a(t_data *data)
{
	int	target;

	target = find_bigger(data->stack_b);
	while (data->stack_b)
	{
		while (data->stack_b->value != target)
		{
			if (find_dir(data->stack_b, target) < 0)
				rotate(data, 'b');
			else
				reverse_rotate(data, 'b');
		}
		push(data, 'a');
		if (data->stack_b)
			target = find_bigger(data->stack_b);
	}
}

void	sort(t_data *data)
{
	int	*values_targets;
	int	size;

	size = determine_chunk_size(count_list(data->stack_a));;
	values_targets = find_smallests(data->stack_a, size);
	while (size > 0)
	{
		if (!is_in_chunk(values_targets, data->stack_a->value, size))
			rotate(data, 'a');
		else
		{
			push(data, 'b');
			size = determine_chunk_size(count_list(data->stack_a));
			free (values_targets);
			values_targets = find_smallests(data->stack_a, size);
		}
	}
	free (values_targets);
	push_all_to_a(data);
}
