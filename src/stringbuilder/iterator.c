/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 23:38:55 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/28 22:32:44 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/stringbuilder.h"

void	sb_iterator_init(t_sb_iterator *iterator, \
const t_vector *vector)
{
	vector_iterator_init(iterator, vector);
}

int	sb_iterator_next(t_sb_iterator *iterator)
{
	return (vector_iterator_next(iterator));
}

int	sb_iterator_prev(t_sb_iterator *iterator)
{
	return (vector_iterator_prev(iterator));
}

char	sb_iterator_current(t_sb_iterator *iterator)
{
	return (sb_get(iterator->vector, iterator->index));
}

bool	sb_iterator_is_end(const t_sb_iterator *iterator)
{
	return (vector_iterator_is_end(iterator));
}
