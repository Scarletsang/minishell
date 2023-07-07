/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:36:33 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 04:19:03 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/string.h"
#include "LIBFT/stringbuilder/clipper.h"
#include "MINISHELL/execution/command.h"

t_ms_status	ms_execute_assignments(struct s_ms *ms, \
t_sb_vector *assignments)
{
	t_ft_vector_iterator	iterator;

	if (ms_executor_envp_import_from_environment(&ms->executor, &ms->vars) \
		== PROGRAM_ERROR)
		return (PROGRAM_ERROR);
	ft_vector_iterator_begin(&iterator, assignments);
	while (!iterator.is_end)
	{
		if (ms_executor_envp_set(&ms->executor, \
			((t_ft_sb *) ft_vector_iterator_current(&iterator))->buffer) \
				== PROGRAM_ERROR)
			return (PROGRAM_ERROR);
		ft_vector_iterator_next(&iterator);
	}
	return (PROGRAM_SUCCESS);
}

t_ms_status	ms_execute_declares(struct s_ms *ms, \
t_sb_vector *assignments)
{
	t_ft_vector_iterator	iterator;
	t_ft_sb					*value_sb;
	char					*value;

	ft_vector_iterator_begin(&iterator, assignments);
	while (!iterator.is_end)
	{
		value_sb = ft_vector_iterator_current(&iterator);
		value = ft_strchr(value_sb->buffer, '=');
		if (ms_vars_declare(&ms->vars, \
			ft_str_slice(value_sb->buffer, 0, \
				value - (char *) value_sb->buffer), \
			(t_ft_str_nt){value_sb->buffer, value_sb->size}) == PROGRAM_ERROR)
			return (PROGRAM_ERROR);
		ft_vector_iterator_next(&iterator);
	}
	return (PROGRAM_SUCCESS);
}
