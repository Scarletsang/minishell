/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:16:44 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/22 05:02:09 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/vector.h"
#include <stdio.h>

void	vector_buffer_shift(t_vector *vector, size_t to, size_t from)
{
	size_t	distance;

	if (vector->size == 0)
		return ;
	if ((from < to) && (to < vector->capacity))
	{
		distance = to - from;
		to = vector->size - 1 + distance;
		from += distance;
		while (to > from)
		{
			vector_set(vector, to, vector_get(vector, to - distance));
			to--;
		}
		vector_set(vector, to, vector_get(vector, to - distance));
	}
	else if ((from > to) && (from < vector->capacity))
	{
		distance = from - to;
		while (to < vector->size)
		{
			vector_set(vector, to, vector_get(vector, to + distance));
			to++;
		}
	}
}

void	vector_buffer_copy_from(t_vector *vector, void *buffer, size_t index, \
size_t copy_amount)
{
	while ((index < vector->capacity) && (copy_amount > 0))
	{
		vector_set(vector, index, buffer);
		buffer += vector->item_size;
		index++;
		copy_amount--;
	}
}
