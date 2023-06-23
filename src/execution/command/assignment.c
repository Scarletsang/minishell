/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:36:33 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 17:59:33 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution.h"

t_executor_exit_code	ms_execute_assignments(struct s_ms *ms, \
t_sb_vector *assignments)
{
	t_ft_vector_iterator	iterator;

	if (ms_executor_envp_import_from_environment(&ms->executor, &ms->vars) \
		== EXECUTION_ERROR)
		return (EXECUTION_ERROR);
	ft_vector_iterator_init(&iterator, assignments);
	while (!ft_vector_iterator_is_end(&iterator))
	{
		if (ms_executor_envp_set(&ms->executor, \
			((t_ft_sb *) ft_vector_iterator_current(&iterator))->buffer))
			return (EXECUTION_ERROR);
		ft_vector_iterator_next(&iterator);
	}
	return (EXECUTION_SUCCESS);
}
