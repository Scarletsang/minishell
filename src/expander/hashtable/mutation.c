/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 00:35:00 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/13 04:35:48 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/expander/hashtable.h"

static int	ht_add_item(struct s_ht *ht, struct s_ht_item *item, char *key,
	void *value)
{
	if (item->key)
		return (EXIT_FAILURE);
	item->key = key;
	item->value = value;
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
	if (ht_add_item(ht, item, key, value) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	interval = hash_for_interval(key, ht->capacity);
	while (item->key)
	{
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
	if (!item->key)
		return ;
	if (ft_strcmp(item->key, key) == 0)
	{
		ht_del_item(ht, item);
		return ;
	}
	interval = hash_for_interval(key, ht->capacity);
	while (item->key)
	{
		index = (index + interval) % ht->capacity;
		item = &ht->items[index];
		if (ft_strcmp(item->key, key) == 0)
		{
			ht_del_item(ht, item);
			return ;
		}
	}
}