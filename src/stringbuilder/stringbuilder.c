/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringBuilder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:19:07 by htsang            #+#    #+#             */
/*   Updated: 2023/05/17 19:17:01 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/stringbuilder.h"

int	sb_create(struct s_sb *sb, const t_sb_size capacity)
{
	sb->buffer = ft_calloc(capacity, sizeof(char));
	if (!sb->buffer)
		return (EXIT_FAILURE);
	sb->capacity = capacity;
	sb->size = 0;
	return (EXIT_SUCCESS);
}

int	sb_resize(struct s_sb *sb)
{
	char		*new_buffer;
	t_sb_size	new_capacity;

	if (sb->capacity == SB_MAX_SIZE)
		return (EXIT_FAILURE);
	new_capacity = sb->capacity * 2;
	if (new_capacity > (SB_MAX_SIZE / 2))
		new_capacity = SB_MAX_SIZE;
	new_buffer = ft_calloc(new_capacity, sizeof(char));
	if (!new_buffer)
		return (EXIT_FAILURE);
	ft_memcpy(new_buffer, sb->buffer, sb->size);
	free(sb->buffer);
	sb->buffer = new_buffer;
	sb->capacity = new_capacity;
	return (EXIT_SUCCESS);
}

void	sb_destroy(struct s_sb *sb)
{
	free(sb->buffer);
	sb->buffer = NULL;
	sb->capacity = 0;
	sb->size = 0;
}
