/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 00:35:00 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/17 16:18:17 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/hashtable.h"

static int	ht_add_item(struct s_ht *ht, struct s_ht_item *item, char *key,
	void *value)
{
	if (item->key)
		return (EXIT_FAILURE);
	item->key = key;
	item->value = value;
	item->deleted = false;
	ht->occupied++;
	if (ht->occupied * 100 / ht->capacity > 70)
		return (ht_rehash(ht));
	return (EXIT_SUCCESS);
}

/**
 * @brief Add a key-value pair to the hash table. The key and value
 * must be malloced.
 * @param ht The hash table.
 * @param key The key.
 * @param value The value.
 * @return int EXIT_SUCCESS if the key-value pair is added successfully,
*/
int	ht_add(struct s_ht *ht, char *key, void *value)
{
	t_ht_index			index;
	t_ht_index			interval;
	struct s_ht_item	*item;

	index = hash(key, ht->capacity);
	item = &ht->items[index];
	if (item->key && (ft_strcmp(item->key, key) == 0))
		return (EXIT_FAILURE);
	if (ht_add_item(ht, item, key, value) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	interval = hash_for_interval(key, ht->capacity);
	while (item->key)
	{
		if (ft_strcmp(item->key, key) == 0)
			return (EXIT_FAILURE);
		index = (index + interval) % ht->capacity;
		item = &ht->items[index];
	}
	return (ht_add_item(ht, item, key, value));
}

void	ht_del_item(struct s_ht *ht, struct s_ht_item *item)
{
	if (item->key)
		free(item->key);
	if (item->value)
		free(item->value);
	item->key = NULL;
	item->value = NULL;
	item->deleted = true;
	ht->occupied--;
}

/**
 * @brief Delete a key-value pair from the hash table.
 * @param ht The hash table.
 * @param key The key.
*/
void	ht_del(struct s_ht *ht, char *key)
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
		ht_del_item(ht, item);
		return ;
	}
	interval = hash_for_interval(key, ht->capacity);
	while (item->key || item->deleted)
	{
		index = (index + interval) % ht->capacity;
		item = &ht->items[index];
		if (item->key && (ft_strcmp(item->key, key) == 0))
		{
			ht_del_item(ht, item);
			return ;
		}
	}
}

int	ht_update(struct s_ht *ht, char *key, void *value)
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
		item->value = value;
		return (EXIT_SUCCESS);
	}
	interval = hash_for_interval(key, ht->capacity);
	while (item->key || item->deleted)
	{
		index = (index + interval) % ht->capacity;
		item = &ht->items[index];
		if (item->key && (ft_strcmp(item->key, key) == 0))
		{
			item->value = value;
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}