/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:36:33 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 01:22:41 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	struct s_ft_sb_clipper	clipper;
	char					*key;
	t_ft_sb					*value_sb;

	ft_vector_iterator_begin(&iterator, assignments);
	while (!iterator.is_end)
	{
		value_sb = ft_vector_iterator_current(&iterator);
		ft_sb_clipper_init(&clipper, value_sb);
		ft_sb_clipper_area(&clipper, NULL, "=");
		key = ft_sb_clipper_run(&clipper);
		if (ms_vars_declare(&ms->vars, key, value_sb->buffer) == PROGRAM_ERROR)
		{
			free(key);
			return (PROGRAM_ERROR);
		}
		free(key);
		ft_vector_iterator_next(&iterator);
	}
	return (PROGRAM_SUCCESS);
}
