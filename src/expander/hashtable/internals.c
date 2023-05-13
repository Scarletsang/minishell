/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 00:52:50 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/13 01:44:25 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/expander/hashtable.h"

t_ht_index	hash(char *key, t_ht_index capacity)
{
	unsigned long	hash;
	t_ht_index		i;

	hash = 0;
	i = 0;
	while (key[i])
	{
		hash += key[i];
		i++;
	}
	return (hash % capacity);
}

t_ht_index	hash_for_interval(char *key, t_ht_index capacity)
{
	unsigned long	hash;
	t_ht_index		i;

	hash = 0;
	i = 0;
	while (key[i])
	{
		hash += key[i];
		i++;
	}
	return (7 - (hash % 7) % capacity);
}

static void	ht_clone(struct s_ht *dest, struct s_ht *src)
{
	dest->capacity = src->capacity;
	dest->items = src->items;
	dest->occupied = src->occupied;
}

int	ht_rehash(struct s_ht *ht)
{
	t_ht_index			i;
	struct s_ht			old_ht;
	struct s_ht_item	*item;

	ht_clone(&old_ht, ht);
	if (ht_create(ht, ht->capacity * 2))
	{
		ht_clone(ht, &old_ht);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < old_ht.capacity)
	{
		item = &old_ht.items[i];
		if (!item->key)
			continue ;
		ht_add(ht, item->key, item->value);
		i++;
	}
	free(old_ht.items);
	return (EXIT_SUCCESS);
}
