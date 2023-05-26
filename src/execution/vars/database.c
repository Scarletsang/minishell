/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:25:31 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/26 13:25:04 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"

char	*minishell_vars_extract_key(const t_sb *key_and_value)
{
	t_sb	key;
	size_t	key_len;

	key_len = sb_strchr_len(key_and_value, '=');
	if (!sb_search_success(key_and_value, key_len))
		return (NULL);
	if (sb_init(&key, key_len))
		return (NULL);
	if (sb_perform(&key, sb_action_append_len(\
		(const char *) key_and_value->buffer, key_len)))
	{
		sb_free(&key);
		return (NULL);
	}
	return ((char *) key.buffer);
}

int	minishell_vars_database_set(t_ht *database, const t_sb *key_and_value)
{
	char	*key;

	key = minishell_vars_extract_key(key_and_value);
	if (!key)
		return (EXIT_FAILURE);
	if (ht_update(database, key, key_and_value->buffer, free))
	{
		free(key);
		return (EXIT_FAILURE);
	}
	free(key);
	return (EXIT_SUCCESS);
}

char	*minishell_vars_database_get(t_ht *database, const t_sb *key_and_value)
{
	char	*key;
	char	*result;

	key = minishell_vars_extract_key(key_and_value);
	if (!key)
		key = (char *) key_and_value->buffer;
	result = ht_get(database, key);
	free(key);
	return (result);
}
