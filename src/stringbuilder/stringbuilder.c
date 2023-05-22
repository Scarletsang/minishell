/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:19:07 by htsang            #+#    #+#             */
/*   Updated: 2023/05/22 15:02:21 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/stringbuilder.h"

int	sb_init(t_sb *sb, const size_t capacity)
{
	if (vector_init(sb, sizeof(char), capacity + 1, vector_set_char))
		return (EXIT_FAILURE);
	vector_set(sb, 0, "\0");
	sb->size = 1;
	return (EXIT_SUCCESS);
}

int	sb_resize(t_sb *sb)
{
	return (vector_resize(sb));
}

void	sb_free(t_sb *sb)
{
	vector_free(sb);
}
