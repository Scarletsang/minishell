/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 01:02:40 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/execution/command/builtins.h"
#include "LIBFT/ctype.h"
#include "MINISHELL/error_printer.h"

bool	name_is_valid_indentifier(char *name, char delimeter)
{
	if (!name)
		return (false);
	if (!ft_isalpha(*name) && *name != '_')
		return (false);
	while (*name && *name != delimeter)
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
	char						*key;

	if (command->size == 1)
		return (EC_SUCCESS);
	exit_code = EC_SUCCESS;
	ft_vector_iterator_init(&vec_iter, command);
	ft_vector_iterator_next(&vec_iter);
	while (!vec_iter.is_end)
	{
		key = ((t_ft_sb *)ft_vector_iterator_current(&vec_iter))->buffer;
		if (!name_is_valid_indentifier(key, '\0'))
		{
			ms_error_printer_builtin("unset", key,
				"not a valid identifier");
			exit_code = EC_FAILURE;
		}
		else
			ms_vars_unset(&ms->vars, key);
		ft_vector_iterator_next(&vec_iter);
	}
	return (exit_code);
}
