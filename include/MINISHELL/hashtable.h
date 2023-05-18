/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 23:08:04 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/18 06:28:32 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include <stdlib.h>
# include "libft.h"
# include <stdbool.h>

typedef unsigned int	t_ht_index;

struct s_ht_item
{
	char	*key;
	void	*value;
	bool	deleted;
};

/**
 * The hash table is implemented with open addressing, and double hashing
 * as the startegy for resolving collisions. One hash function is used to
 * calculate the index of the storing item, and another hash function is
 * used to calculate the interval between each probing for that particular
 * item.
*/
struct s_ht
{
	t_ht_index			capacity;
	t_ht_index			occupied;
	struct s_ht_item	*items;
};

/////////////////////////////////////
////////     interface     //////////
/////////////////////////////////////

int			ht_create(struct s_ht *ht, const t_ht_index capacity);

int			ht_add(struct s_ht *ht, const char *key, const void *value);

int			ht_update(struct s_ht *ht, const char *key, const void *value);

void		*ht_get(struct s_ht *ht, const char *key);

void		ht_del(struct s_ht *ht, const char *key);

void		ht_destroy(struct s_ht *ht);

/////////////////////////////////////////////////
////////     unprotected interface     //////////
/////////////////////////////////////////////////

int			ht_unsafe_add_item(struct s_ht *ht, struct s_ht_item *item, \
const char *key, const void *value);

void		ht_unsafe_del_item(struct s_ht *ht, struct s_ht_item *item);

int			ht_unsafe_update_item(struct s_ht_item *item, const void *value);

/////////////////////////////////////
////////     internals     //////////
/////////////////////////////////////

t_ht_index	hash(const char *key, t_ht_index capacity);

t_ht_index	hash_for_interval(const char *key, t_ht_index capacity);

int			ht_rehash(struct s_ht *ht);

/////////////////////////////////////
////////      Printer      //////////
/////////////////////////////////////

void		ht_print(struct s_ht *ht);

#endif