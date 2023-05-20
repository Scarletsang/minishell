/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 23:30:47 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/20 04:37:33 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/hashtable.h"
#include <stdio.h>

int	ht_create(struct s_ht *ht, const t_ht_index capacity)
{
	ht->capacity = capacity;
	ht->occupied = 0;
	ht->entries = ft_calloc(capacity, sizeof(struct s_ht_entry));
	if (!ht->entries)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ht_destroy(struct s_ht *ht)
{
	t_ht_index	i;

	i = 0;
	while ((ht->occupied > 0) && (i < ht->capacity))
	{
		ht_entry_delete(&ht->entries[i]);
		ht->occupied--;
		i++;
	}
	free(ht->entries);
}

/**
 * @brief Get the value of a key from the hash table.
 * @param ht The hash table.
 * @param key The key.
 * @return void* The value of the key, or NULL if the key is not found.
*/
void	*ht_get(struct s_ht *ht, const char *key)
{
	t_ht_index			index;
	t_ht_index			interval;
	struct s_ht_entry	*entry;

	index = hash(key, ht->capacity);
	entry = &ht->entries[index];
	if (!entry->key && !entry->deleted)
		return (NULL);
	if (entry->key && (ft_strcmp(entry->key, key) == 0))
		return (entry->value);
	interval = hash_for_interval(key, ht->capacity);
	index = (index + interval) % ht->capacity;
	entry = &ht->entries[index];
	while (entry->key || entry->deleted)
	{
		if (entry->key && (ft_strcmp(entry->key, key) == 0))
			return (entry->value);
		index = (index + interval) % ht->capacity;
		entry = &ht->entries[index];
	}
	return (NULL);
}


struct s_ht_entry	*ht_get_item(struct s_ht *ht, const char *key)
{
	t_ht_index			index;
	t_ht_index			interval;
	struct s_ht_entry	*entry;

	index = hash(key, ht->capacity);
	entry = &ht->entries[index];
	if (!(entry->key || entry->deleted))
		return (NULL);
	if (entry->key && ft_strcmp(entry->key, key) == 0)
		return (entry);
	interval = hash_for_interval(key, ht->capacity);
	while (entry->key || entry->deleted)
	{
		index = (index + interval) % ht->capacity;
		entry = &ht->entries[index];
		if (entry->key && (ft_strcmp(entry->key, key) == 0))
			return (entry);
	}
	return (NULL);
}

struct s_ht_entry	*ht_get_empty_item(struct s_ht *ht, const char *key)
{
	t_ht_index			index;
	t_ht_index			interval;
	struct s_ht_entry	*entry;

	index = hash(key, ht->capacity);
	entry = &ht->entries[index];
	if (!entry->key)
		return (entry);
	if (ft_strcmp(entry->key, key) == 0)
		return (NULL);
	interval = hash_for_interval(key, ht->capacity);
	while (entry->key)
	{
		index = (index + interval) % ht->capacity;
		entry = &ht->entries[index];
		if (entry->key && (ft_strcmp(entry->key, key) == 0))
			return (NULL);
	}
	return (entry);
}
