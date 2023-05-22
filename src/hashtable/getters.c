/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:43:08 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/22 14:43:30 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/hashtable.h"

/**
 * @brief Get the value of a key from the hash table.
 * @param ht The hash table.
 * @param key The key.
 * @return void* The value of the key, or NULL if the key is not found.
*/
void	*ht_get(t_ht *ht, const char *key)
{
	struct s_ht_entry	*entry;

	entry = ht_get_entry(ht, key);
	if (!entry)
		return (NULL);
	return (entry->value);
}

struct s_ht_entry	*ht_get_entry(t_ht *ht, const char *key)
{
	size_t				index;
	size_t				interval;
	struct s_ht_entry	*entry;

	index = hash(key, ht->capacity);
	entry = vector_get(ht, index);
	if (!(entry->key || entry->deleted))
		return (NULL);
	if (entry->key && ft_strcmp(entry->key, key) == 0)
		return (entry);
	interval = hash_for_interval(key, ht->capacity);
	while (entry->key || entry->deleted)
	{
		index = (index + interval) % ht->capacity;
		entry = vector_get(ht, index);
		if (entry->key && (ft_strcmp(entry->key, key) == 0))
			return (entry);
	}
	return (NULL);
}

struct s_ht_entry	*ht_get_empty_entry(t_ht *ht, const char *key)
{
	size_t				index;
	size_t				interval;
	struct s_ht_entry	*entry;

	index = hash(key, ht->capacity);
	entry = vector_get(ht, index);
	if (!entry->key)
		return (entry);
	if (ft_strcmp(entry->key, key) == 0)
		return (NULL);
	interval = hash_for_interval(key, ht->capacity);
	while (entry->key)
	{
		index = (index + interval) % ht->capacity;
		entry = vector_get(ht, index);
		if (entry->key && (ft_strcmp(entry->key, key) == 0))
			return (NULL);
	}
	return (entry);
}
