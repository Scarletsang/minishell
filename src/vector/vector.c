/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:19 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/22 14:30:27 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/vector.h"

int	vector_init(t_vector *vector, size_t item_size, size_t capacity, \
t_vector_setter setter)
{
	vector->buffer = ft_calloc(capacity, item_size);
	if (!vector->buffer)
		return (EXIT_FAILURE);
	vector->capacity = capacity;
	vector->item_size = item_size;
	vector->size = 0;
	if (!setter)
		vector->setter = (t_vector_setter) vector_set_char;
	else
		vector->setter = setter;
	return (EXIT_SUCCESS);
}

void	*vector_get(t_vector *vector, size_t index)
{
	return (vector->buffer + (index * vector->item_size));
}

void	vector_set(t_vector *vector, size_t index, void *data)
{
	vector->setter(vector_get(vector, index), data);
}

int	vector_resize(t_vector *vector)
{
	char	*old_buffer;
	size_t	new_capacity;

	if (vector->capacity == SIZE_MAX)
		return (EXIT_FAILURE);
	new_capacity = vector->capacity * 2;
	if (new_capacity > (SIZE_MAX / 2))
		new_capacity = SIZE_MAX;
	old_buffer = vector->buffer;
	vector->buffer = malloc(vector->item_size * new_capacity);
	if (!vector->buffer)
		return (EXIT_FAILURE);
	vector_buffer_copy_from(vector, old_buffer, 0, vector->size);
	free(old_buffer);
	vector->capacity = new_capacity;
	return (EXIT_SUCCESS);
}

void	vector_free(t_vector *vector)
{
	free(vector->buffer);
	vector->buffer = NULL;
	vector->item_size = 0;
	vector->size = 0;
	vector->capacity = 0;
	vector->setter = NULL;
}
