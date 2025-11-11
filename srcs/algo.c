/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:54:37 by theo              #+#    #+#             */
/*   Updated: 2025/11/11 13:10:29 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*find_list_of_smaller(t_node *head, int size)
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

static void	sort_stack_b(t_data *data)
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

void	swiss_sort(t_data *data)
{
	int	*values_targets;
	int	size;

	size = determine_chunk_size(count_list(data->stack_a));
	values_targets = find_list_of_smaller(data->stack_a, size);
	while (size > 0)
	{
		if (!is_in_chunk(values_targets, data->stack_a->value, size))
			rotate(data, 'a');
		else
		{
			push(data, 'b');
			size = determine_chunk_size(count_list(data->stack_a));
			free (values_targets);
			values_targets = find_list_of_smaller(data->stack_a, size);
			if (!values_targets)
				return ;
		}
	}
	free (values_targets);
	sort_stack_b(data);
}
