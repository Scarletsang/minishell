/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:25:31 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/07/07 01:47:53 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"

const struct s_ft_ht_entry	*ms_vars_database_set(t_ft_ht *database, \
t_ft_str key, t_ft_str_nt value)
{
	return (ft_ht_update(database, key, value, free));
}

t_ft_str_nt	ms_vars_database_get(const t_ft_ht *database, t_ft_str key)
{
	return (ft_ht_get(database, key));
}
