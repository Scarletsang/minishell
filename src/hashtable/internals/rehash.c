/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rehash.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 04:17:16 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/20 04:22:05 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/hashtable.h"

static void	ht_clone(struct s_ht *dest, struct s_ht *src)
{
	dest->capacity = src->capacity;
	dest->entries = src->entries;
	dest->occupied = src->occupied;
}

static int	ht_import(struct s_ht *ht, struct s_ht_entry *entry)
{
	struct s_ht_entry	*new_entry;

	new_entry = ht_get_empty_item(ht, entry->key);
	if (!new_entry)
		return (EXIT_FAILURE);
	new_entry->key = entry->key;
	new_entry->value = entry->value;
	new_entry->deleted = entry->deleted;
	new_entry->is_owned = entry->is_owned;
	ht->occupied++;
	return (EXIT_SUCCESS);
}

int	ht_rehash(struct s_ht *ht)
{
	t_ht_index			i;
	struct s_ht			old_ht;
	struct s_ht_entry	*old_entry;

	ht_clone(&old_ht, ht);
	if (ht_create(ht, ht->capacity * 2))
	{
		ht_clone(ht, &old_ht);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < old_ht.capacity)
	{
		old_entry = &old_ht.entries[i++];
		if (!old_entry->key)
			continue ;
		if (ht_import(ht, old_entry))
		{
			ht_clone(ht, &old_ht);
			return (EXIT_FAILURE);
		}
	}
	free(old_ht.entries);
	return (EXIT_SUCCESS);
}