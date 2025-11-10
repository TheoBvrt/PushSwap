/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:41:38 by theo              #+#    #+#             */
/*   Updated: 2025/11/10 16:03:43 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_stack(t_node **from_stack, t_node **to_stack, char *str)
{
	t_node	*tmp;

	tmp = *from_stack;
	if (count_list(*from_stack) < 1)
		return ;
	*from_stack = (*from_stack)->next;
	tmp->next = *to_stack;
	*to_stack = tmp;
	ft_printf("%s\n", str);
}

void	push(t_data *data, int stack)
{
	if (stack == 'a')
		push_stack(&data->stack_b, &data->stack_a, "pa");
	else
		push_stack(&data->stack_a, &data->stack_b, "pb");
}
