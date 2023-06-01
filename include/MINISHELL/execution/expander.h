/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 02:47:08 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/30 22:14:03 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "MINISHELL/execution/vars.h"
# include "MINISHELL/stringbuilder.h"
# include "MINISHELL/stringbuilder/clipper.h"

# define SUPPORTED_SPECIAL_VARS "?\0$"

///////////////////////////////////////
///////////    expander    ////////////
///////////////////////////////////////

int	minishell_expander(t_sb *sb, const struct s_minishell_vars *vars);

////////////////////////////////////////////////
///////////    private interface    ////////////
////////////////////////////////////////////////

int	minishell_expander_match_any(t_sb_iterator *it, const char *set);

int	minishell_expander_dquote_dollar(t_sb_iterator *it, \
const struct s_minishell_vars *vars);

#endif