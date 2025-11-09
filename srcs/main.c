/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:04:01 by theo              #+#    #+#             */
/*   Updated: 2025/11/09 01:27:36 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stdio.h"

int	init(t_data *data, char *args)
{
	data->stack_a = NULL;
	data->stack_b = NULL;
	if (!parse_string(data, args))
		return (0);
	print_list(data->stack_a);
	return (1);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("[Erreur] -> nombre d'arguments invalide\n", 2);
		return (1);
	}
	if (!init(&data, argv[1]))
		return (1);
	free_list(&data.stack_a);
	return (0);
}
