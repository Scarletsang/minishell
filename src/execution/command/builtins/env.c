/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 04:06:39 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/execution/command/builtins.h"
#include "LIBFT/string.h"
#include "LIBFT/io.h"

t_ms_exit_code	ms_execute_builtin_env(struct s_ms *ms, t_sb_vector *command)
{
	size_t					i;
	struct s_ft_ht_entry	*entry;

	(void) command;
	i = 0;
	while (i < ms->vars.environment.capacity)
	{
		entry = ft_vector_get(&ms->vars.environment, i);
		if (entry->key && ft_strchr(entry->value.content, '='))
			ft_putendl_fd((char *) entry->value.content, STDOUT_FILENO);
		i++;
	}
	return (EC_SUCCESS);
}
