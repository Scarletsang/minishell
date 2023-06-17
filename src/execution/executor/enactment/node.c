/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:36:33 by htsang            #+#    #+#             */
/*   Updated: 2023/06/17 17:49:36 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor/enactment.h"

t_executor_exit_code	ms_executor_enact_assignment(\
struct s_ms_executor *executor, t_sb_vector *assignment, struct s_ms *ms)
{
	t_vector_iterator	iterator;

	if (ms_executor_envp_import_from_environment(executor, &ms->vars) \
		== EXECUTION_ERROR)
		return (EXECUTION_ERROR);
	vector_iterator_init(&iterator, assignment);
	while (!vector_iterator_is_end(&iterator))
	{
		if (ms_executor_envp_set(executor, &ms->vars, \
			((t_sb *) vector_iterator_current(&iterator))->buffer))
			return (EXECUTION_ERROR);
		vector_iterator_next(&iterator);
	}
	return (EXECUTION_SUCCESS);
}

t_executor_exit_code	ms_executor_enact_command_execution(\
struct s_ms_executor *executor, t_sb_vector *command, struct s_ms *ms)
{

}
