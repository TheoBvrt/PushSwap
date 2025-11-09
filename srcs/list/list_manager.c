/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:51:39 by theo              #+#    #+#             */
/*   Updated: 2025/11/09 00:46:18 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_list(t_node **head)
{
	t_node	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free (tmp);
		tmp = NULL;
	}
	*head = NULL;
}

void	pop_back(t_node **head)
{
	t_node	*tmp;

	tmp = *head;
	if (!*head)
		return ;
	if (!tmp->next)
	{
		free (tmp);
		*head = NULL;
		return ;
	}
	while (tmp->next->next)
		tmp = tmp->next;
	free (tmp->next);
	tmp->next = NULL;
}

void	pop_front(t_node **head)
{
	t_node	*tmp;

	tmp = *head;
	if (!*head)
		return ;
	*head = (*head)->next;
	free (tmp);
}

void	add_front(t_node **head, t_node *new)
{
	new->next = *head;
	*head = new;
}

t_node *create_node(int value)
{
	t_node	*new;
	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_back(t_node	**head, t_node *new)
{
	t_node *tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	new->next = tmp->next;
	tmp->next = new;
}

void	print_list(t_node *head)
{
	while (head)
	{
		ft_printf("[%d] -> ", head->value);
		head = head->next;
	}
	ft_printf("[NULL]\n");
}
