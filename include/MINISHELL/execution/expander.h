/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 02:47:08 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/07 16:28:02 by htsang           ###   ########.fr       */
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

int	ms_expander(t_sb *sb, const struct s_ms_vars *vars);

////////////////////////////////////////////////
///////////    private interface    ////////////
////////////////////////////////////////////////

int	ms_expander_match_any(t_sb_iterator *it, const char *set);

int	ms_expander_dquote_dollar(t_sb_iterator *it, \
const struct s_ms_vars *vars);

#endif