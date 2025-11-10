/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 22:39:45 by theo              #+#    #+#             */
/*   Updated: 2025/11/10 23:17:59 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_smaller(t_node *head)
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

int	find_bigger(t_node *head)
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

int	find_dir(t_node *head, int value)
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
