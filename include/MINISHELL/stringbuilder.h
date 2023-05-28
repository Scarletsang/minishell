/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:19:47 by htsang            #+#    #+#             */
/*   Updated: 2023/05/29 00:07:56 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGBUILDER_H
# define STRINGBUILDER_H

# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include "libft.h"
# include "MINISHELL/vector.h"

////////////////////////////////////////////////
////////     String Builder action    //////////
////////////////////////////////////////////////

/**
 * @brief A String Builder action stores information about the a string
 * builder operation.
 * @param entry_str The string to be inserted into the string builder.
 * @param entry_str_len The length of the string to be inserted into the string
 * builder.
 * @param edit_start The index of the string builder where the string will be
 * inserted.
 * @param edit_len The length of the string to be replaced in the string builder.
 * @param field_validator A bit field that indicates which fields are valid. It
 * is needed because some actions may not need all the fields.
*/
struct s_sb_action
{
	const char		*entry_str;
	size_t			entry_str_len;
	size_t			edit_start;
	size_t			edit_len;
	unsigned int	field_validator : 3;
};

// append (str, MAX, MAX, MAX)
// insert (str, MAX, start, MAX)
// replace (str, MAX, start, len)
// delete ([NULL], 0, start, len)
// append_len (str, len, MAX, MAX)
// insert_len (str, len, start, MAX)
// replace_len (str, len, start, len)

struct s_sb_action			sb_action_append(const char *str);

struct s_sb_action			sb_action_append_len(const char *str, \
const size_t str_len);

struct s_sb_action			sb_action_insert(const char *str, \
const size_t edit_start);

struct s_sb_action			sb_action_insert_len(const char *str, \
const size_t str_len, const size_t edit_start);

struct s_sb_action			sb_action_delete(const size_t edit_start, \
const size_t edit_len);

struct s_sb_action			sb_action_replace(const char *str, \
const size_t edit_start, const size_t edit_len);

struct s_sb_action			sb_action_replace_len(const char *str, \
const size_t str_len, const size_t edit_start, const size_t edit_len);

/////////////////////////////////////////////////////////////////
////////     String Builder action field validator     //////////
/////////////////////////////////////////////////////////////////

enum e_sb_validator_bit
{
	SB_ENTRY_STR_LEN_BIT = 0b1,
	SB_EDIT_START_BIT = 0b10,
	SB_EDIT_LEN_BIT = 0b100
};

void						sb_action_set_validator_bit(\
struct s_sb_action *action, enum e_sb_validator_bit bit);

void						sb_action_flip_validator_bit(\
struct s_sb_action *action, enum e_sb_validator_bit bit);

bool						sb_action_has_entry_str_len(\
struct s_sb_action *action);

bool						sb_action_has_edit_start(\
struct s_sb_action *action);

bool						sb_action_has_edit_len(struct s_sb_action *action);

/////////////////////////////////////////
////////     String Builder    //////////
/////////////////////////////////////////

/**
 * @brief The String builder allows easy and efficient construction of strings
 * from smaller pieces. It is implemented as a dynamic array of characters.
*/
typedef t_vector			t_sb;

int							sb_init(t_sb *sb, const size_t capacity);

char						sb_get(const t_sb *sb, const size_t index);

int							sb_perform(t_sb *sb, struct s_sb_action action);

int							sb_resize(t_sb *sb);

void						sb_free(t_sb *sb);

/////////////////////////////////////////////////
////////     String Builder iterator   //////////
/////////////////////////////////////////////////

/**
 * @brief The String builder iterator iterates over the string contained
 * in the string builder.
*/
typedef t_vector_iterator	t_sb_iterator;

void						sb_iterator_init(t_sb_iterator *iterator, \
const t_vector *vector);

int							sb_iterator_next(t_sb_iterator *iterator);

int							sb_iterator_prev(t_sb_iterator *iterator);

char						sb_iterator_current(t_sb_iterator *iterator);

bool						sb_iterator_is_end(const t_sb_iterator *iterator);

#endif