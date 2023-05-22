/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:26:09 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/22 03:07:48 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/vector.h"

int	vector_append(t_vector *vector, void *data)
{
	if (vector->size == vector->capacity)
		if (vector_resize(vector))
			return (EXIT_FAILURE);
	vector_set(vector, vector->size, data);
	vector->size++;
	return (EXIT_SUCCESS);
}

int	vector_insert(t_vector *vector, void *data, size_t index)
{
	if (index > vector->size)
		return (EXIT_FAILURE);
	if (vector->size == vector->capacity)
		if (vector_resize(vector))
			return (EXIT_FAILURE);
	vector_buffer_shift(vector, index + 1, index);
	vector_set(vector, index, data);
	vector->size++;
	return (EXIT_SUCCESS);
}

int	vector_remove(t_vector *vector, size_t index)
{
	if (index >= vector->size)
		return (EXIT_FAILURE);
	vector_buffer_shift(vector, index, index + 1);
	vector->size--;
	return (EXIT_SUCCESS);
}
