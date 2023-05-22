/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:44:56 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/22 14:46:48 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>
# include <limits.h>
# include "libft.h"

typedef void	(*t_vector_setter)(void *buffer, void *data);

typedef struct	s_vector
{
	void			*buffer;
	size_t			item_size;
	size_t			size;
	size_t			capacity;
	t_vector_setter	setter;
}				t_vector;

int		vector_init(t_vector *vector, size_t item_size, \
size_t capacity, t_vector_setter setter);

void	*vector_get(t_vector *vector, size_t index);

void	vector_set(t_vector *vector, size_t index, void *data);

int		vector_resize(t_vector *vector);

void	vector_free(t_vector *vector);

////////////////////////////////////////////
////////////     actions     ///////////////
////////////////////////////////////////////

int		vector_append(t_vector *vector, void *data);

int		vector_insert(t_vector *vector, void *data, size_t index);

int		vector_remove(t_vector *vector, size_t index);

////////////////////////////////////////////
////////////     setters     ///////////////
////////////////////////////////////////////

void	vector_set_char(void *buffer, void *character);

void	vector_set_string(void *buffer, void *string);

void	vector_set_ptr(void *buffer, void *ptr);

void	vector_set_int(void *buffer, void *integer);

/////////////////////////////////////////////
////////////      buffers      //////////////
/////////////////////////////////////////////

void	vector_buffer_shift(t_vector *vector, size_t to, size_t from);

void	vector_buffer_copy_from(t_vector *vector, void *buffer, \
size_t index, size_t copy_amount);

#endif