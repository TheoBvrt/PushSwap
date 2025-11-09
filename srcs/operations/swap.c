/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:41:17 by theo              #+#    #+#             */
/*   Updated: 2025/11/09 13:28:26 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_stack(t_node **head, char *str)
{
	t_node	*tmp;

	tmp = *head;
	if (count_list(*head) < 2)
		return ;
	*head = (*head)->next;
	tmp->next = (*head)->next;
	(*head)->next = tmp;
	ft_printf("%s\n", str);
}

void	swap(t_data *data, int stack)
{
	if (stack == 'a')
		swap_stack(&data->stack_a, "sa");
	else if (stack == 'b')
		swap_stack(&data->stack_b, "sb");
	else
	{
		swap_stack(&data->stack_a, "sa");
		swap_stack(&data->stack_b, "sb");
	}
}
