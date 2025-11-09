/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:54:37 by theo              #+#    #+#             */
/*   Updated: 2025/11/09 15:36:54 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_smallest(t_node *head)
{
	int	value;

	value = head->value;
	while (head)
	{
		if (head->value < value)
			value = head->value;
		head = head->next;
	}
	return (value);
}

void	sort(t_data *data)
{
	int	value_target;
	// print_list(data->stack_a);
	// print_list(data->stack_b);
	value_target = find_smallest(data->stack_a);
	while (data->stack_a)
	{
		while (data->stack_a->value != value_target)
			rotate(data, 'a');
		push(data, 'b');
		if (data->stack_a)
			value_target = find_smallest(data->stack_a);
	}
	while (data->stack_b)
		push(data, 'a');
	// print_list(data->stack_a);
}
