/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 23:30:47 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/13 11:17:38 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/expander/hashtable.h"

int	ht_create(struct s_ht *ht, const t_ht_index capacity)
{
	ht->capacity = capacity;
	ht->occupied = 0;
	ht->items = ft_calloc(capacity, sizeof(struct s_ht_item));
	if (!ht->items)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ht_destroy(struct s_ht *ht)
{
	t_ht_index	i;

	i = 0;
	while (i < ht->capacity)
	{
		ht_del_item(ht, &ht->items[i]);
		i++;
	}
	free(ht->items);
}

/**
 * @brief Get the value of a key from the hash table.
 * @param ht The hash table.
 * @param key The key.
 * @return void* The value of the key, or NULL if the key is not found.
*/
void	*ht_get(struct s_ht *ht, char *key)
{
	t_ht_index			index;
	t_ht_index			interval;
	struct s_ht_item	*item;

	index = hash(key, ht->capacity);
	item = &ht->items[index];
	if (!item->key && !item->deleted)
		return (NULL);
	if (item->key && (ft_strcmp(item->key, key) == 0))
		return (item->value);
	interval = hash_for_interval(key, ht->capacity);
	index = (index + interval) % ht->capacity;
	item = &ht->items[index];
	while (item->key || item->deleted)
	{
		if (item->key && (ft_strcmp(item->key, key) == 0))
			return (item->value);
		index = (index + interval) % ht->capacity;
		item = &ht->items[index];
	}
	return (NULL);
}
