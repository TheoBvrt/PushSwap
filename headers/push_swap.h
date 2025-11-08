/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:16:55 by theo              #+#    #+#             */
/*   Updated: 2025/11/09 00:29:09 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"

typedef struct s_node t_node;

typedef	struct s_node
{
	int		value;
	t_node	*prev;
	t_node	*next;
}	t_node;


typedef struct s_data
{
	t_node	*stack_a;
	t_node	*stack_b;
}	t_data;

//List
t_node	*create_node(int value);
void	add_back(t_node	**head, t_node *new);
void	free_list(t_node **head);
void	pop_back(t_node **head);
void	pop_front(t_node **head);
void	add_front(t_node **head, t_node *new);
void	print_list(t_node *head);

//Parser
int	parse_string(t_data *data, char *str);

//Utils
void	free_tab(char **tab);

#endif
