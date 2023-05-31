/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:55:14 by htsang            #+#    #+#             */
/*   Updated: 2023/05/22 02:09:27 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/stringbuilder.h"

struct s_sb_action	sb_action_delete(const size_t edit_start, \
const size_t edit_len)
{
	return ((struct s_sb_action){
		.entry_str = NULL,
		.edit_start = edit_start,
		.edit_len = edit_len,
		.field_validator = 0 | SB_EDIT_START_BIT | SB_EDIT_LEN_BIT
	});
}

struct s_sb_action	sb_action_replace(const char *str, \
const size_t edit_start, const size_t edit_len)
{
	return ((struct s_sb_action){
		.entry_str = str,
		.edit_start = edit_start,
		.edit_len = edit_len,
		.field_validator = 0 | SB_EDIT_START_BIT | SB_EDIT_LEN_BIT
	});
}

struct s_sb_action	sb_action_replace_len(const char *str, \
const size_t str_len, const size_t edit_start, const size_t edit_len)
{
	return ((struct s_sb_action){
		.entry_str = str,
		.entry_str_len = str_len,
		.edit_start = edit_start,
		.edit_len = edit_len,
		.field_validator = 0 | SB_ENTRY_STR_LEN_BIT | SB_EDIT_START_BIT | \
			SB_EDIT_LEN_BIT
	});
}