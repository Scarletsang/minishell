/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:10:42 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/16 22:54:16 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/stringbuilder/clipper.h"

void	sb_clipper_init(struct s_sb_clipper *clipper, const t_sb *sb)
{
	clipper->sb = sb;
	clipper->lbound = 0;
	clipper->rbound = sb->size - 1;
}

char	sb_clipper_at_lbound(const struct s_sb_clipper *clipper)
{
	return (sb_get(clipper->sb, clipper->lbound));
}

char	sb_clipper_at_rbound(const struct s_sb_clipper *clipper)
{
	return (sb_get(clipper->sb, clipper->rbound));
}
