/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 20:13:24 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 19:27:56 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/builtins.h"

t_ms_status	ms_builtin_start(struct s_ms *ms, t_sb_vector *command)
{
	// enact assignment
	// save stdin and stdout
	(void) command;
	(void) ms;
	return (PROGRAM_SUCCESS);
}

t_ms_status	ms_builtin_end(struct s_ms *ms, t_sb_vector *command)
{
	// enact builtin
	// restore stdin and stdout
	(void) command;
	(void) ms;
	return (PROGRAM_SUCCESS);
}
