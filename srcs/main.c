/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:04:01 by theo              #+#    #+#             */
/*   Updated: 2025/11/10 18:29:47 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stdio.h"

int	init(t_data *data, int argc, char **argv)
{
	data->stack_a = NULL;
	data->stack_b = NULL;
	if (!parser(data, argc, argv))
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		return (0);
	if (!init(&data, argc, argv))
	{
		free_list(&data.stack_a);
		return (1);
	}
	if (is_sorted(&data))
		return (0);
	sort(&data);
	free_list(&data.stack_a);
	return (0);
}
