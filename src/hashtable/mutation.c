/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 00:35:00 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/18 06:28:48 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/hashtable.h"

/**
 * @brief Add a key-value pair to the hash table. The key and value
 * must be malloced.
 * @param ht The hash table.
 * @param key The key.
 * @param value The value.
 * @return int EXIT_SUCCESS if the key-value pair is added successfully,
*/
int	ht_add(struct s_ht *ht, const char *key, const void *value)
{
	t_ht_index			index;
	t_ht_index			interval;
	struct s_ht_item	*item;

	index = hash(key, ht->capacity);
	item = &ht->items[index];
	if (item->key && (ft_strcmp(item->key, key) == 0))
		return (EXIT_FAILURE);
	if (ht_unsafe_add_item(ht, item, key, value) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	interval = hash_for_interval(key, ht->capacity);
	while (item->key)
	{
		if (ft_strcmp(item->key, key) == 0)
			return (EXIT_FAILURE);
		index = (index + interval) % ht->capacity;
		item = &ht->items[index];
	}
	return (ht_unsafe_add_item(ht, item, key, value));
}

/**
 * @brief Delete a key-value pair from the hash table.
 * @param ht The hash table.
 * @param key The key.
*/
void	ht_del(struct s_ht *ht, const char *key)
{
	t_ht_index			index;
	t_ht_index			interval;
	struct s_ht_item	*item;

	index = hash(key, ht->capacity);
	item = &ht->items[index];
	if (!item->key && !item->deleted)
		return ;
	if (item->key && (ft_strcmp(item->key, key) == 0))
	{
		ht_unsafe_del_item(ht, item);
		return ;
	}
	interval = hash_for_interval(key, ht->capacity);
	while (item->key || item->deleted)
	{
		index = (index + interval) % ht->capacity;
		item = &ht->items[index];
		if (item->key && (ft_strcmp(item->key, key) == 0))
		{
			ht_unsafe_del_item(ht, item);
			return ;
		}
	}
}

int	ht_update(struct s_ht *ht, const char *key, const void *value)
{
	t_ht_index			index;
	t_ht_index			interval;
	struct s_ht_item	*item;

	index = hash(key, ht->capacity);
	item = &ht->items[index];
	if (!item->key && !item->deleted)
		return (EXIT_FAILURE);
	if (item->key && (ft_strcmp(item->key, key) == 0))
	{
		return (ht_unsafe_update_item(item, value));
	}
	interval = hash_for_interval(key, ht->capacity);
	while (item->key || item->deleted)
	{
		index = (index + interval) % ht->capacity;
		item = &ht->items[index];
		if (item->key && (ft_strcmp(item->key, key) == 0))
		{
			return (ht_unsafe_update_item(item, value));
		}
	}
	return (EXIT_FAILURE);
}