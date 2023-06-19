/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:25:31 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/19 15:39:36 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"

int	ms_vars_database_set(t_ft_ht *database, const char *key, \
const char *value)
{
	if (!ft_ht_update(database, key, value, free))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

const char	*ms_vars_database_get(const t_ft_ht *database, const char *key)
{
	return (ft_ht_get(database, key));
}
