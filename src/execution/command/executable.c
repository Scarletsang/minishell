/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:04:28 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 21:14:55 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution.h"

t_ms_exit_code	ms_execute_executable(struct s_ms *ms, \
t_sb_vector *command)
{
	(void)command;
	(void)ms;
	return (EC_COMMAND_NOT_FOUND);
}
