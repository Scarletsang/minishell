/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/06/30 22:29:09 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/execution/command/builtins.h"
#include "LIBFT/ctype.h"
#include "MINISHELL/error_printer.h"

bool	name_is_valid_indentifier(char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (false);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
		name++;
	}
	return (true);
}

t_ms_exit_code	ms_execute_builtin_unset(struct s_ms *ms, t_sb_vector *command)
{
	t_ms_exit_code				exit_code;
	struct s_ft_vector_iterator	vec_iter;
	char						*entry_key;

	if (command->size == 1)
		return (EC_SUCCESS);
	exit_code = EC_SUCCESS;
	ft_vector_iterator_init(&vec_iter, command);
	ft_vector_iterator_next(&vec_iter);
	while (!ft_vector_iterator_is_end(&vec_iter))
	{
		entry_key = ((t_ft_sb *)ft_vector_iterator_current(&vec_iter))->buffer;
		if (!name_is_valid_indentifier(entry_key))
		{
			ms_error_printer_builtin("unset", entry_key,
				"not a valid identifier");
			exit_code = EC_FAILURE;
			ft_vector_iterator_next(&vec_iter);
			continue ;
		}
		ms_vars_unset(&ms->vars, entry_key);
		ft_vector_iterator_next(&vec_iter);
	}
	return (exit_code);
}
