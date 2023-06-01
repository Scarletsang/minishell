/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:25:31 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/01 02:16:28 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"

int	minishell_vars_database_set(t_ht *database, const char *key, \
const char *value)
{
	if (!ht_update(database, key, value, free))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

const char	*minishell_vars_database_get(const t_ht *database, const char *key)
{
	return (ht_get(database, key));
}
