/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 00:35:00 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/26 12:34:15 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/hashtable.h"

/**
 * @brief Add a key-value pair to the hash table. The key and value
 * must be malloced.
 * @param ht The hash table.
 * @param key The key.
 * @param value The value.
 * @param owned_by_ht Specify whether the value is owned by the hash table.
 * @return int EXIT_SUCCESS if the key-value pair is added successfully,
 * EXIT_FAILURE otherwise.
*/
int	ht_set(t_ht *ht, const char *key, const void *value, \
t_ht_entry_cleaner cleaner)
{
	struct s_ht_entry	*entry;

	entry = ht_get_empty_entry(ht, key);
	if (!entry)
		return (EXIT_FAILURE);
	if (ht_entry_set_key(entry, key) || \
		ht_entry_set_value(entry, value, cleaner))
	{
		ht_entry_delete(entry);
		return (EXIT_FAILURE);
	}
	ht->size++;
	if (ht->size * 100 / ht->capacity > 70)
		return (ht_resize(ht));
	return (EXIT_SUCCESS);
}

/**
 * @brief Delete a key-value pair from the hash table.
 * @param ht The hash table.
 * @param key The key.
*/
void	ht_del(t_ht *ht, const char *key)
{
	struct s_ht_entry	*entry;

	entry = ht_get_entry(ht, key);
	if (!entry)
		return ;
	ht_entry_delete(entry);
	ht->size--;
}

/**
 * @brief Update the value of a key-value pair in the hash table.
 * @param ht The hash table.
 * @param key The key.
 * @param value The value.
 * @param owned_by_ht Specify whether the value is owned by the hash table.
 * @return int EXIT_SUCCESS if the value is updated successfully,
 * EXIT_FAILURE otherwise.
*/
int	ht_update(t_ht *ht, const char *key, const void *value, \
t_ht_entry_cleaner cleaner)
{
	struct s_ht_entry	*entry;

	entry = ht_get_entry(ht, key);
	if (!entry)
		return (ht_set(ht, key, value, cleaner));
	if (ht_entry_set_value(entry, value, cleaner))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
