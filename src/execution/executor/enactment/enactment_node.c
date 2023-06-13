/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enactment_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:36:33 by htsang            #+#    #+#             */
/*   Updated: 2023/06/13 23:46:54 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

t_executor_exit_code	ms_executor_enact_assignment(\
struct s_ms_executor *executor, t_sb_vector *assignment, struct s_ms *ms)
{
	// iterate through assignment in assignment and append it to the assignment
	//   vector in executor
	// ms_vars_set_envp(ms->vars, assignment);
	
}

t_executor_exit_code	ms_executor_enact_redirection_in(\
struct s_ms_executor *executor, t_AST_redirection_vector *redirection_in, \
struct s_ms *ms)
{

}

t_executor_exit_code	ms_executor_enact_redirection_out(\
struct s_ms_executor *executor, t_AST_redirection_vector *redirection_out, \
struct s_ms *ms)
{

}

t_executor_exit_code	ms_executor_enact_command_execution(\
struct s_ms_executor *executor, t_sb_vector *command, struct s_ms *ms)
{

}
