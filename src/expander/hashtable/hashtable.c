/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 23:30:47 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/13 01:44:00 by anthonytsan      ###   ########.fr       */
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
	free(ht);
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
	if (!item->key)
		return (NULL);
	if (ft_strcmp(item->key, key) == 0)
		return (item->value);
	interval = hash_for_interval(key, ht->capacity);
	while (item->key)
	{
		index = (index + interval) % ht->capacity;
		item = &ht->items[index];
		if (ft_strcmp(item->key, key) == 0)
			return (item->value);
	}
	return (NULL);
}
