/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 00:52:50 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/18 06:26:14 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/hashtable.h"

t_ht_index	hash(const char *key, t_ht_index capacity)
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

static bool	is_coprime(t_ht_index a, t_ht_index b)
{
	t_ht_index	tmp;

	while (b != 0)
	{
		tmp = b;
		b = a % b;
		a = tmp;
	}
	return (a == 1);
}

t_ht_index	hash_for_interval(const char *key, t_ht_index capacity)
{
	unsigned long	hash;
	t_ht_index		interval;
	t_ht_index		max_interval;

	hash = 0;
	while (*key)
	{
		hash += *key;
		key++;
	}
	max_interval = capacity * 7 / 10;
	interval = max_interval - (hash % max_interval);
	while (!is_coprime(capacity, interval))
	{
		interval = (interval + 1) % max_interval;
	}
	return (interval);
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
		item = &old_ht.items[i++];
		if (!item->key)
			continue ;
		ht_add(ht, item->key, item->value);
	}
	free(old_ht.items);
	return (EXIT_SUCCESS);
}
