/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 04:21:23 by htsang           ###   ########.fr       */
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
	t_ft_str_nt					key;

	if (command->size == 1)
		return (EC_SUCCESS);
	exit_code = EC_SUCCESS;
	ft_vector_iterator_begin(&vec_iter, command);
	while (!ft_vector_iterator_next(&vec_iter))
	{
		key = (t_ft_str_nt){
			.content = \
				((t_ft_sb *) ft_vector_iterator_current(&vec_iter))->buffer,
			.size = ((t_ft_sb *)ft_vector_iterator_current(&vec_iter))->size
		};
		if (!name_is_valid_indentifier(key.content, '\0'))
		{
			ms_error_printer_builtin("unset", key.content,
				"not a valid identifier");
			exit_code = EC_FAILURE;
		}
		else
			ms_vars_unset(&ms->vars, key);
	}
	return (exit_code);
}
