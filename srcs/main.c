/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:04:01 by theo              #+#    #+#             */
/*   Updated: 2025/11/11 12:03:39 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stdio.h"

static int	init(t_data *data, int argc, char **argv)
{
	data->stack_a = NULL;
	data->stack_b = NULL;
	if (!parser(data, argc, argv))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		return (0);
	if (!init(&data, argc, argv))
	{
		free_list(&data.stack_a);
		return (0);
	}
	if (!is_sorted(&data))
		sort(&data);
	free_list(&data.stack_a);
	return (0);
}
