/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 23:38:55 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/28 22:30:00 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/vector.h"

void	vector_iterator_init(t_vector_iterator *iterator, \
const t_vector *vector)
{
	iterator->vector = vector;
	iterator->index = 0;
}

int	vector_iterator_next(t_vector_iterator *iterator)
{
	if (iterator->index < iterator->vector->size)
	{
		iterator->index++;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	vector_iterator_prev(t_vector_iterator *iterator)
{
	if (iterator->index > 0)
	{
		iterator->index--;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	*vector_iterator_current(t_vector_iterator *iterator)
{
	return (vector_get(iterator->vector, iterator->index));
}

bool	vector_iterator_is_end(const t_vector_iterator *iterator)
{
	return (iterator->index == iterator->vector->size);
}
