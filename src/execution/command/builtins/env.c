/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/06/30 20:19:26 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/execution/command/builtins.h"
#include <stdio.h>

t_ms_exit_code	ms_execute_builtin_env(struct s_ms *ms, t_sb_vector *command)
{
	size_t					i;
	struct s_ft_ht_entry	*entry;

	(void) command;
	i = 0;
	while (i < ms->vars.environment.capacity)
	{
		entry = ft_vector_get(&ms->vars.environment, i);
		if (entry->key)
			printf("%s\n", (char *) entry->value);
		i++;
	}
	return (EXIT_SUCCESS);
}
