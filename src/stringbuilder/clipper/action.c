/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:53:54 by htsang            #+#    #+#             */
/*   Updated: 2023/06/16 22:54:24 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/stringbuilder/clipper.h"

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
	return (string_slice_to_cstring(sb_clipper_slice(clipper)));
}

t_string_slice	sb_clipper_slice(const struct s_sb_clipper *clipper)
{
	return ((t_string_slice){
		.content = clipper->sb->buffer + clipper->lbound,
		.size = clipper->rbound - clipper->lbound + 1
	});
}
