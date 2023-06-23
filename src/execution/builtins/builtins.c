/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 20:13:24 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 17:52:02 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/builtins.h"

t_executor_exit_code	ms_builtin_start(struct s_ms *ms, t_sb_vector *command)
{
	// enact assignment
	// save stdin and stdout
	(void) command;
	(void) ms;
	return (EXECUTION_SUCCESS);
}

t_executor_exit_code	ms_builtin_end(struct s_ms *ms, t_sb_vector *command)
{
	// enact builtin
	// restore stdin and stdout
	(void) command;
	(void) ms;
	return (EXECUTION_SUCCESS);
}
