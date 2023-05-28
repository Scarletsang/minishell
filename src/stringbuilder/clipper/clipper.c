/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:10:42 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/28 23:03:58 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/stringbuilder/clipper.h"

void	sb_clipper_init(struct s_sb_clipper *clipper, const t_sb *sb)
{
	clipper->sb = sb;
	clipper->lbound = 0;
	clipper->rbound = sb->size - 1;
}

int	sb_clipper_move_lbound(struct s_sb_clipper *clipper)
{
	if ((clipper->lbound + 1) >= clipper->rbound)
		return (EXIT_FAILURE);
	clipper->lbound++;
	return (EXIT_SUCCESS);
}

int	sb_clipper_move_rbound(struct s_sb_clipper *clipper)
{
	if (clipper->rbound <= (clipper->lbound + 1))
		return (EXIT_FAILURE);
	clipper->rbound--;
	return (EXIT_SUCCESS);
}

char	*sb_clipper_run(const struct s_sb_clipper *clipper)
{
	char			*result;
	t_sb_iterator	it;
	size_t			i;

	result = malloc(sizeof(char) * (clipper->rbound - \
		clipper->lbound + 1));
	if (!result)
		return (NULL);
	sb_iterator_init(&it, clipper->sb);
	it.index = clipper->lbound;
	i = 0;
	while (it.index <= clipper->rbound)
	{
		result[i] = sb_iterator_current(&it);
		i++;
		sb_iterator_next(&it);
	}
	result[i] = '\0';
	return (result);
}
