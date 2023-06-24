/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 02:47:08 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/24 13:32:21 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "MINISHELL/execution/vars.h"
# include "LIBFT/stringbuilder.h"
# include "LIBFT/stringbuilder/sb_iterator.h"

# define SUPPORTED_SPECIAL_VARS "?\0$"

///////////////////////////////////////
///////////    expander    ////////////
///////////////////////////////////////

int	ms_expander(t_ft_sb *sb, const struct s_ms_vars *vars);

int	ms_expander_remove_quotes(t_ft_sb *sb);

////////////////////////////////////////////////
///////////    private interface    ////////////
////////////////////////////////////////////////

int	ms_expander_match_any(t_ft_sb_iterator *it, const char *set);

int	ms_expander_dollar(t_ft_sb_iterator *it, \
const struct s_ms_vars *vars, const char *match_end);

#endif