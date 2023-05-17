/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:55:14 by htsang            #+#    #+#             */
/*   Updated: 2023/05/17 19:26:48 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/stringbuilder.h"

struct s_sb_action	sb_action_delete(const t_sb_size edit_start, \
const t_sb_size edit_len)
{
	return ((struct s_sb_action){
		.entry_str = NULL,
		.edit_start = edit_start,
		.edit_len = edit_len,
		.field_validator = 0 | SB_EDIT_START_BIT | SB_EDIT_LEN_BIT
	});
}

struct s_sb_action	sb_action_replace(const char *str, \
const t_sb_size edit_start, const t_sb_size edit_len)
{
	return ((struct s_sb_action){
		.entry_str = str,
		.edit_start = edit_start,
		.edit_len = edit_len,
		.field_validator = 0 | SB_EDIT_START_BIT | SB_EDIT_LEN_BIT
	});
}

struct s_sb_action	sb_action_replace_len(const char *str, \
const t_sb_size str_len, const t_sb_size edit_start, const t_sb_size edit_len)
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
