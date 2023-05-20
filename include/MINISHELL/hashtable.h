/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 23:08:04 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/20 04:24:12 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include <stdlib.h>
# include "libft.h"
# include <stdbool.h>

typedef unsigned int	t_ht_index;

/**
 * A hash table entry 
*/
struct s_ht_entry
{
	char	*key;
	void	*value;
	bool	deleted;
	bool	is_owned;
};

void				ht_entry_init(struct s_ht_entry *entry);

void				ht_entry_delete(struct s_ht_entry *entry);

int					ht_entry_set_key(struct s_ht_entry *entry, const char *key);

int					ht_entry_set_value(struct s_ht_entry *entry, \
const void *value, bool owned_by_ht);

/**
 * The hash table is implemented with open addressing, and double hashing
 * as the startegy for resolving collisions. One hash function is used to
 * calculate the index of the storing entry, and another hash function is
 * used to calculate the interval between each probing for that particular
 * entry.
*/
struct s_ht
{
	t_ht_index			capacity;
	t_ht_index			occupied;
	struct s_ht_entry	*entries;
};

/////////////////////////////////////
////////     interface     //////////
/////////////////////////////////////

int					ht_create(struct s_ht *ht, const t_ht_index capacity);

void				ht_destroy(struct s_ht *ht);

void				*ht_get(struct s_ht *ht, const char *key);

struct s_ht_entry	*ht_get_item(struct s_ht *ht, const char *key);

struct s_ht_entry	*ht_get_empty_item(struct s_ht *ht, const char *key);

int					ht_add(struct s_ht *ht, const char *key, const void *value, \
bool owned_by_ht);

int					ht_update(struct s_ht *ht, const char *key, \
const void *value, bool owned_by_ht);

void				ht_del(struct s_ht *ht, const char *key);

/////////////////////////////////////
////////     internals     //////////
/////////////////////////////////////

t_ht_index			hash(const char *key, t_ht_index capacity);

t_ht_index			hash_for_interval(const char *key, t_ht_index capacity);

int					ht_rehash(struct s_ht *ht);

/////////////////////////////////////
////////      Printer      //////////
/////////////////////////////////////

void				ht_print(struct s_ht *ht);

#endif