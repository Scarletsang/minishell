/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:09:57 by htsang            #+#    #+#             */
/*   Updated: 2023/05/18 00:10:33 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/stringbuilder.h"

static void	sb_injection_word(struct s_sb *sb, struct s_sb_action *action)
{
	t_sb_size	replace_word_end;

	replace_word_end = action->edit_start + action->edit_len;
	ft_memmove(sb->buffer + action->edit_start + action->entry_str_len, \
		sb->buffer + replace_word_end, sb->size - replace_word_end);
	ft_memcpy(sb->buffer + action->edit_start, action->entry_str, \
		action->entry_str_len);
	sb->size += action->entry_str_len - action->edit_len;
	sb->buffer[sb->size] = 0;
}

static int	sb_perform_delete(struct s_sb *sb, struct s_sb_action *action)
{
	t_sb_size	remaining_size;

	if (action->edit_start > sb->size)
		return (EXIT_FAILURE);
	remaining_size = sb->size - action->edit_start;
	if (action->edit_len >= remaining_size)
	{
		sb->buffer[action->edit_start] = 0;
		sb->size = action->edit_start;
		return (EXIT_SUCCESS);
	}
	remaining_size -= action->edit_len;
	sb->size -= action->edit_len;
	ft_memmove(sb->buffer + action->edit_start, \
		sb->buffer + action->edit_start + action->edit_len, remaining_size);
	sb->buffer[sb->size] = 0;
	return (EXIT_SUCCESS);
}

/**
 * @brief Replace a substring with another string.
 * @details
 * 1. Check if replacement index is valid. Otherwise, return error.
 * 2. Check if buffer has enough space to insert the string. Otherwise, resize
 * the buffer.
 * 3. Offset the substring after the replacement index by the difference
 * between the replacement string length and the substring length.
 * 4. Copy the replacement string at the replacement index.
*/
static int	sb_perform_replace(struct s_sb *sb, struct s_sb_action *action)
{
	if (action->edit_start > sb->size)
		return (EXIT_FAILURE);
	if (action->edit_start + action->edit_len > sb->size)
		action->edit_len = sb->size - action->edit_start;
	if (action->entry_str_len > action->edit_len)
	{
		while (sb->size + action->entry_str_len - \
			action->edit_len >= sb->capacity)
			if (sb_resize(sb))
				return (EXIT_FAILURE);
	}
	sb_injection_word(sb, action);
	return (EXIT_SUCCESS);
}

/**
 * @brief Insert a string at a given position in the buffer.
 * @details
 * 1. Check if insertion index is valid. Otherwise, return error.
 * 2. Check if buffer has enough space to insert the string. Otherwise, resize
 * the buffer.
 * 3. Offset the substring after the insertion index by the insertion string
 * length.
 * 4. Copy the insertion string at the insertion index.
*/
static int	sb_perform_insert(struct s_sb *sb, struct s_sb_action *action)
{
	if (action->edit_start > sb->size)
		return (EXIT_FAILURE);
	while (sb->size + action->entry_str_len >= sb->capacity)
	{
		if (sb_resize(sb))
			return (EXIT_FAILURE);
	}
	sb_injection_word(sb, action);
	return (EXIT_SUCCESS);
}

int	sb_perform(struct s_sb *sb, struct s_sb_action action)
{
	if (!action.entry_str)
		return (sb_perform_delete(sb, &action));
	if (!sb_action_has_entry_str_len(&action))
	{
		action.entry_str_len = ft_strlen(action.entry_str);
		action.field_validator |= SB_ENTRY_STR_LEN_BIT;
	}
	if (sb_action_has_edit_len(&action))
	{
		return (sb_perform_replace(sb, &action));
	}
	action.edit_len = 0;
	action.field_validator |= SB_EDIT_LEN_BIT;
	if (!sb_action_has_edit_start(&action))
	{
		action.edit_start = sb->size;
		action.field_validator |= SB_EDIT_START_BIT;
	}
	return (sb_perform_insert(sb, &action));
}
