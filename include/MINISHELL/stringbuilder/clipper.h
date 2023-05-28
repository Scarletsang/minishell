/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:14:25 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/28 23:02:21 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIPPER_H
# define CLIPPER_H

# include "MINISHELL/stringbuilder.h"
# include "MINISHELL/vector.h"

struct s_sb_clipper
{
	const t_sb	*sb;
	size_t		lbound;
	size_t		rbound;
};

void	sb_clipper_init(struct s_sb_clipper *clipper, const t_sb *sb);

int		sb_clipper_move_lbound(struct s_sb_clipper *clipper);

int		sb_clipper_move_rbound(struct s_sb_clipper *clipper);

char	*sb_clipper_run(const struct s_sb_clipper *clipper);

int		sb_clipper_area(struct s_sb_clipper *clipper, const char *start_match, \
const char *end_match);

#endif