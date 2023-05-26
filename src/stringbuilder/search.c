/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:28:52 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/26 13:40:28 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/stringbuilder.h"

size_t	sb_strchr_len(const t_sb *sb, const char c)
{
	size_t	i;
	char	*str;

	i = 0;
	while (i < sb->size)
	{
		str = vector_get(sb, i);
		if (*str == c)
			return (i);
		i++;
	}
	return (sb->size);
}

bool	sb_search_success(const t_sb *sb, const size_t result)
{
	return (result < sb->size);
}
