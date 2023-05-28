/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 23:08:04 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/29 00:02:15 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include <stdlib.h>
# include <stdbool.h>
# include "libft.h"
# include "MINISHELL/vector.h"

typedef void		(*t_ht_entry_cleaner)(void *);

/**
 * A hash table entry 
*/
struct s_ht_entry
{
	char				*key;
	void				*value;
	bool				deleted;
	t_ht_entry_cleaner	cleaner;
};

void				ht_entry_init(struct s_ht_entry *entry);

void				ht_entry_delete(struct s_ht_entry *entry);

int					ht_entry_set_key(struct s_ht_entry *entry, const char *key);

int					ht_entry_set_value(struct s_ht_entry *entry, \
void *value, t_ht_entry_cleaner cleaner);

/**
 * The hash table is implemented with open addressing, and double hashing
 * as the startegy for resolving collisions. One hash function is used to
 * calculate the index of the storing entry, and another hash function is
 * used to calculate the interval between each probing for that particular
 * entry.
*/
typedef t_vector	t_ht;

///////////////////////////////////////////
////////     basic interface     //////////
///////////////////////////////////////////

int					ht_init(t_ht *ht, const size_t capacity);

void				*ht_get(t_ht *ht, const char *key);

int					ht_set(t_ht *ht, const char *key, void *value, \
t_ht_entry_cleaner cleaner);

int					ht_resize(t_ht *ht);

void				ht_free(t_ht *ht);

//////////////////////////////////////////////
////////     additional getters     //////////
//////////////////////////////////////////////

struct s_ht_entry	*ht_get_entry(t_ht *ht, const char *key);

struct s_ht_entry	*ht_get_empty_entry(t_ht *ht, const char *key);

//////////////////////////////////////////////
////////     additional setters     //////////
//////////////////////////////////////////////

int					ht_update(t_ht *ht, const char *key, \
void *value, t_ht_entry_cleaner cleaner);

void				ht_del(t_ht *ht, const char *key);

////////////////////////////////
////////     hash     //////////
////////////////////////////////

size_t				hash(const char *key, size_t capacity);

size_t				hash_for_interval(const char *key, size_t capacity);

/////////////////////////////////////
////////      Printer      //////////
/////////////////////////////////////

void				ht_print(t_ht *ht);

#endif