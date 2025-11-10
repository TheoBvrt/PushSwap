/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 23:55:04 by theo              #+#    #+#             */
/*   Updated: 2025/11/10 18:28:07 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_data *data)
{
	t_node	*tmp;
	int		value;

	tmp = data->stack_a;	
	value = tmp->value;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (value > tmp->value)
			return (0);
		value = tmp->value;
	}
	return (1);
}

int	determine_chunk_size(int list_size)
{
	if (list_size > 100 && list_size <= 500)
		return (20);
	if (list_size > 15 && list_size <= 100)
		return (15);
	else if (list_size > 0)
		return (1);
	else
		return (0);
}

int	is_in_chunk(int *values_targets, int current, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		if (current == values_targets[index])
			return (1);
		index ++;
	}
	return (0);
}

void	free_tab(char **tab)
{
	int	index;

	index = 0;
	while (tab[index])
	{
		free(tab[index]);
		index ++;
	}
	free(tab);
}
