/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:25:31 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/29 00:08:19 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"

const struct s_ft_ht_entry	*ms_vars_database_set(t_ft_ht *database, \
const char *key, const char *value)
{
	return (ft_ht_update(database, key, value, free));
}

const char	*ms_vars_database_get(const t_ft_ht *database, const char *key)
{
	return (ft_ht_get(database, key));
}
