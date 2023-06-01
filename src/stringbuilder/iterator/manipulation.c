/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:44:51 by htsang            #+#    #+#             */
/*   Updated: 2023/05/30 17:00:55 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/stringbuilder/sb_iterator.h"

int	sb_iterator_mut_insert(t_sb_iterator *iterator, const char *str)
{
	size_t	sb_size;

	sb_size = iterator->vector->size;
	if (sb_perform((t_sb *) iterator->vector, \
		sb_action_insert(str, iterator->index)))
		return (EXIT_FAILURE);
	iterator->index += iterator->vector->size - sb_size;
	return (EXIT_SUCCESS);
}

int	sb_iterator_mut_insert_len(t_sb_iterator *iterator, const char *str, \
const size_t str_len)
{
	if (sb_perform((t_sb *) iterator->vector, \
		sb_action_insert_len(str, str_len, iterator->index)))
		return (EXIT_FAILURE);
	iterator->index += str_len;
	return (EXIT_SUCCESS);
}

int	sb_iterator_mut_delete(t_sb_iterator *iterator, const size_t edit_len)
{
	return (sb_perform((t_sb *) iterator->vector, \
		sb_action_delete(iterator->index, edit_len)));
}

int	sb_iterator_mut_replace(t_sb_iterator *iterator, const char *str, \
const size_t edit_len)
{
	size_t	sb_size;

	sb_size = iterator->vector->size;
	if (sb_perform((t_sb *) iterator->vector, \
		sb_action_replace(str, iterator->index, edit_len)))
		return (EXIT_FAILURE);
	if (iterator->vector->size > sb_size)
		iterator->index += iterator->vector->size - sb_size;
	else
		iterator->index -= sb_size - iterator->vector->size;
	return (EXIT_SUCCESS);
}

int	sb_iterator_mut_replace_len(t_sb_iterator *iterator, const char *str, \
const size_t str_len, const size_t edit_len)
{
	size_t	sb_size;

	sb_size = iterator->vector->size;
	if (sb_perform((t_sb *) iterator->vector, \
		sb_action_replace_len(str, str_len, iterator->index, edit_len)))
		return (EXIT_FAILURE);
	if (iterator->vector->size > sb_size)
		iterator->index += iterator->vector->size - sb_size;
	else
		iterator->index -= sb_size - iterator->vector->size;
	return (EXIT_SUCCESS);
}
