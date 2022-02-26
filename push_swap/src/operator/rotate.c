/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkim <nkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:48:48 by nkim              #+#    #+#             */
/*   Updated: 2022/02/25 01:16:08 by nkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int rotate(t_stack *stack)
{
	t_node *head;

	if (stack->len < 2)
		return 0;
	head = stack->head;

	stack->head = stack->head->next;
	stack->head->prev = NULL;

	head->prev = stack->tail;
	stack->tail->next = head;
	stack->tail = head;
	stack->tail->next = NULL;
	return 1;
}