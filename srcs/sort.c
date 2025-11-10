/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:37:08 by theo              #+#    #+#             */
/*   Updated: 2025/11/10 23:17:04 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_2(t_data *data)
{
	if (data->stack_a->value > data->stack_a->next->value)
		swap(data, 'a');
}

static void	sort_3(t_data *data)
{
	int	bigger;

	bigger = find_bigger(data->stack_a);
	if (data->stack_a->value == bigger)
		rotate(data, 'a');
	else if (data->stack_a->next->value == bigger)
		reverse_rotate(data, 'a');
	if (data->stack_a->value > data->stack_a->next->value)
		swap(data, 'a');
}

static void	sort_5(t_data *data)
{
	int	target;

	target = find_smaller(data->stack_a);
	while (data->stack_a->value != target)
	{
		if (find_dir(data->stack_a, target) == -1)
			rotate(data, 'a');
		else
			reverse_rotate(data, 'a');
	}
	push(data, 'b');
	target = find_smaller(data->stack_a);
	while (data->stack_a->value != target)
	{
		if (find_dir(data->stack_a, target) == -1)
			rotate(data, 'a');
		else
			reverse_rotate(data, 'a');
	}
	push(data, 'b');
	sort_3(data);
	push(data, 'a');
	push(data, 'a');
}

void	sort(t_data *data)
{
	int	size;

	size = count_list(data->stack_a);
	if (size == 2)
		sort_2(data);
	else if (size == 3)
		sort_3(data);
	else if (size == 4 || size == 5)
		sort_5(data);
	else
		swiss_sort(data);
}
