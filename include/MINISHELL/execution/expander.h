/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 02:47:08 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/07/07 03:20:56 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "MINISHELL/execution/vars.h"
# include "LIBFT/stringbuilder.h"
# include "LIBFT/stringbuilder/sb_iterator.h"

///////////////////////////////////////
///////////    expander    ////////////
///////////////////////////////////////

int	ms_expander(t_ft_sb *sb, const struct s_ms_vars *vars);

int	ms_expander_remove_quotes(t_ft_sb *sb);

////////////////////////////////////////////////
///////////    private interface    ////////////
////////////////////////////////////////////////

int	ms_expander_dollar(t_ft_sb_iterator *it, \
const struct s_ms_vars *vars);

int	ms_expander_dollar_no_quote(t_ft_sb_iterator *it, \
const struct s_ms_vars *vars);

#endif