/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:50:45 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/20 03:53:25 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/hashtable.h"

void	ht_entry_init(struct s_ht_entry *entry)
{
	entry->key = NULL;
	entry->value = NULL;
	entry->cleaner = NULL;
	entry->deleted = false;
}

void	ht_entry_delete(struct s_ht_entry *entry)
{
	if (entry->key)
		free(entry->key);
	if (entry->cleaner && entry->value)
	{
		entry->cleaner(entry->value);
		if (entry->cleaner != free)
			free(entry->value);
	}
	entry->key = NULL;
	entry->value = NULL;
	entry->cleaner = NULL;
	entry->deleted = true;
}

int	ht_entry_set_key(struct s_ht_entry *entry, const char *key)
{
	entry->deleted = false;
	entry->key = ft_strdup(key);
	if (!entry->key)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ht_entry_set_value(struct s_ht_entry *entry, const void *value, \
t_ht_entry_cleaner cleaner)
{
	if (entry->cleaner && entry->value)
		entry->cleaner(entry->value);
	if (value && cleaner)
	{
		entry->value = ft_strdup(value);
		if (!entry->value)
			return (EXIT_FAILURE);
		entry->cleaner = cleaner;
	}
	else
	{
		entry->value = (void *) value;
		entry->cleaner = NULL;
	}
	return (EXIT_SUCCESS);
}
