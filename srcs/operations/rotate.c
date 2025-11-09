/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:41:33 by theo              #+#    #+#             */
/*   Updated: 2025/11/09 17:07:16 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_stack(t_node **head, char *str)
{
	t_node	*tmp;
	t_node	*cpy;

	tmp = *head;
	if (!tmp)
		return ;
	if (tmp && (*head)->next)
	{
		*head = (*head)->next;
		cpy = *head;
		while (cpy->next)
			cpy = cpy->next;
		cpy->next = tmp;
		tmp->next = NULL;
	}
	ft_printf("%s\n", str);
}

static void	reverse_rotate_stack(t_node **head, char *str)
{
	t_node	*tmp;
	t_node	*cpy;

	tmp = *head;
	if (count_list(*head) < 2)
		return ;
	while (tmp->next->next)
		tmp = tmp->next;
	cpy = tmp->next;
	cpy->next = *head;
	tmp->next = NULL;
	*head = cpy;
	ft_printf("%s\n", str);
}

void	rotate(t_data *data, int stack)
{
	if (stack == 'a')
		rotate_stack(&data->stack_a, "ra");
	else
		rotate_stack(&data->stack_b, "rb");
}

void	reverse_rotate(t_data *data, int stack)
{
	if (stack == 'a')
		reverse_rotate_stack(&data->stack_a, "rra");
	else
		reverse_rotate_stack(&data->stack_b, "rrb");
}
