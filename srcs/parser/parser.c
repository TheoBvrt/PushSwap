/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:22:29 by theo              #+#    #+#             */
/*   Updated: 2025/11/09 01:26:42 by theo             ###   ########.fr       */
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
		ft_putstr_fd("[Erreur] -> les valeurs doivent tenir dans un int", 2);
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
				ft_putstr_fd("[Erreur] -> Présence de doublons\n", 2);
				return (0);
			}
			tmp = tmp->next;
		}
		head = head->next;
		tmp = head;
	}
	return (1);
}

int	parse_string(t_data *data, char *str)
{
	char	**tmp;
	int		index;

	index = 0;
	tmp = ft_split(str, ' ');
	if (!tmp)
		return (0);
	while (tmp[index])
	{
		if (!check_string(tmp[index]))
		{
			ft_putstr_fd("[Erreur] -> merci d'entrer des nombres valides\n", 2);
			return (free_tab(tmp), 0);
		}
		if (!add_string_to_stack(data, tmp[index]))
			return (free_tab(tmp), 0);
		index ++;
	}
	if (!check_doublon(data->stack_a))
		return (free_tab(tmp), 0);
	free_tab(tmp);
	return (1);
}
