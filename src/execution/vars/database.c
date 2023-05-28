/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:25:31 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/29 00:02:48 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/vars.h"

int	minishell_vars_database_set(t_ht *database, const char *key, \
char *value)
{
	if (ht_update(database, key, value, free))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*minishell_vars_database_get(t_ht *database, const char *key)
{
	return (ht_get(database, key));
}
