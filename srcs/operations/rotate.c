/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:41:33 by theo              #+#    #+#             */
/*   Updated: 2025/11/09 15:27:16 by theo             ###   ########.fr       */
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

void	rotate(t_data *data, int stack)
{
	if (stack == 'a')
		rotate_stack(&data->stack_a, "ra");
	else
		rotate_stack(&data->stack_b, "rb");
}
