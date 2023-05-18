/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsafe_mutation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 06:17:24 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/18 06:28:17 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/hashtable.h"

int	ht_unsafe_add_item(struct s_ht *ht, struct s_ht_item *item, \
const char *key, const void *value)
{
	if (item->key)
		return (EXIT_FAILURE);
	item->deleted = false;
	item->key = ft_strdup(key);
	if (!item->key)
		return (EXIT_FAILURE);
	item->value = ft_strdup(value);
	if (!item->value)
	{
		free(item->key);
		return (EXIT_FAILURE);
	}
	ht->occupied++;
	if (ht->occupied * 100 / ht->capacity > 70)
		return (ht_rehash(ht));
	return (EXIT_SUCCESS);
}

void	ht_unsafe_del_item(struct s_ht *ht, struct s_ht_item *item)
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

int	ht_unsafe_update_item(struct s_ht_item *item, const void *value)
{
	if (item->value)
		free(item->value);
	item->value = ft_strdup(value);
	if (!item->value)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
