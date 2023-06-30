/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:19:54 by htsang            #+#    #+#             */
/*   Updated: 2023/06/30 10:21:13 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution.h"
#include "MINISHELL/execution/command.h"

t_ms_status	ms_execute_pipe(struct s_ms *ms, \
struct s_ast_node *pipe)
{
	if (ms_execute_ast_node(ms, pipe->left) == PROGRAM_ERROR)
		return (PROGRAM_ERROR);
	if (ms_execute_ast_node(ms, pipe->right) == PROGRAM_ERROR)
		return (PROGRAM_ERROR);
	return (PROGRAM_SUCCESS);
}

t_ms_status	ms_execute_pipe_last(struct s_ms *ms, \
struct s_ast_node *pipe)
{
	if (ms_execute_ast_node(ms, pipe->left) == PROGRAM_ERROR)
		return (PROGRAM_ERROR);
	if (ms_execute_ast_node_last(ms, pipe->right) == PROGRAM_ERROR)
		return (PROGRAM_ERROR);
	return (PROGRAM_SUCCESS);
}
