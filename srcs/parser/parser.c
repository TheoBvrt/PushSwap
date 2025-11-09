/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:22:29 by theo              #+#    #+#             */
/*   Updated: 2025/11/09 02:16:16 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	add_string_to_stack(t_data *data, char *str)
{
	t_node	*new_node;
	long	value;

	value = ft_atoi(str);
	if (value > 2147483647 || value < -2147483648)
	{
		ft_putstr_fd("Error\n", 2);
		free_list(&data->stack_a);
		return (0);
	}
	new_node = create_node(value);
	if (!new_node)
	{
		free_list(&data->stack_a);
		return (0);
	}
	new_node->value = value;
	add_back(&data->stack_a, new_node);
	return (1);
}

int	check_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0)
		{
			if ((!ft_isdigit(str[i]) && (str[i] != '+' && str[i] != '-'))
				|| ft_strlen(str) == 1 && (str[i] == '+' || str[i] == '-'))
				return (0);
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		i ++;
	}
	return (1);
}

int	check_doublon(t_node *head)
{
	t_node	*tmp;
	int		check;

	tmp = head;
	while (head)
	{
		check = head->value;
		while (tmp)
		{
			if (tmp != head && check == tmp->value)
			{
				ft_putstr_fd("Error\n", 2);
				return (0);
			}
			tmp = tmp->next;
		}
		head = head->next;
		tmp = head;
	}
	return (1);
}

int	parse_the_tab(t_data *data, char **tab)
{
	int		index;

	index = 0;
	while (tab[index])
	{
		if (!check_string(tab[index]))
		{
			ft_putstr_fd("Error\n", 2);
			return (0);
		}
		if (!add_string_to_stack(data, tab[index]))
			return (0);
		index ++;
	}
	if (!check_doublon(data->stack_a))
		return (0);
	return (1);
}

int	parser(t_data *data, int argc, char **argv)
{
	char	**tab;
	int		index;

	index = 1;
	while (index < argc)
	{
		tab = ft_split(argv[index], ' ');
		if (!tab)
			return (0);
		if (!parse_the_tab(data, tab))
			return (free_tab(tab), 0);
		free_tab(tab);
		index ++;
	}
	if (count_list(data->stack_a) == 0)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	return (1);
}
