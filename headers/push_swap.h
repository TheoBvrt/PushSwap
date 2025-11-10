/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:16:55 by theo              #+#    #+#             */
/*   Updated: 2025/11/10 23:20:43 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"

typedef struct s_node	t_node;

typedef struct s_node
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

void	sort(t_data *data);
void	swiss_sort(t_data *data);
int		find_bigger(t_node *head);
int		find_smaller(t_node *head);
int		find_dir(t_node *head, int value);

//List
t_node	*create_node(int value);
void	add_back(t_node	**head, t_node *new);
void	free_list(t_node **head);
void	pop_back(t_node **head);
void	pop_front(t_node **head);
void	add_front(t_node **head, t_node *new);
void	print_list(t_node *head);
int		count_list(t_node *head);

//Parser
int		parser(t_data *data, int argc, char **argv);

//Operations
void	swap(t_data *data, int stack);
void	push(t_data *data, int stack);
void	rotate(t_data *data, int stack);
void	reverse_rotate(t_data *data, int stack);

//Utils
void	free_tab(char **tab);
int		is_in_chunk(int *values_targets, int current, int size);
int		determine_chunk_size(int list_size);
int		is_sorted(t_data *data);

#endif
