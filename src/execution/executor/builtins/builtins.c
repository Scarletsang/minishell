/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 20:13:24 by htsang            #+#    #+#             */
/*   Updated: 2023/06/19 17:33:53 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor/builtins.h"

t_executor_exit_code	ms_builtin_start(struct s_ms_executor *executor, \
t_sb_vector *command, struct s_ms *ms)
{
	// enact assignment
	// save stdin and stdout
	return (EXECUTION_SUCCESS);
}

t_executor_exit_code	ms_builtin_end(struct s_ms_executor *executor, \
t_sb_vector *command, struct s_ms *ms)
{
	// enact builtin
	// restore stdin and stdout
	return (EXECUTION_SUCCESS);
}
