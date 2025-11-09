/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:04:01 by theo              #+#    #+#             */
/*   Updated: 2025/11/09 17:02:14 by theo             ###   ########.fr       */
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
	// ft_printf("stack_a : ");
	// print_list(data.stack_a);
	// ft_printf("stack_b : ");
	// print_list(data.stack_b);
	// ft_printf("---------\n");
	// reverse_rotate(&data, 'b');
	// ft_printf("\n---------\n");
	// ft_printf("stack_a : ");
	// print_list(data.stack_a);
	// ft_printf("stack_b : ");
	// print_list(data.stack_b);
	sort(&data);
	free_list(&data.stack_a);
	return (0);
}
