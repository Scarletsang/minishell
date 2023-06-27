/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:04:28 by htsang            #+#    #+#             */
/*   Updated: 2023/06/25 04:40:03 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution.h"

t_ms_exit_code	ms_execute_executable(struct s_ms *ms, \
t_sb_vector *command)
{
	(void)command;
	(void)ms;
	// if (ms_is_comamnd())
	// {
	// 	if (ms_find_path() == PROGRAM_ERROR)
	// 	{
	// 		// command not foudn error
	// 		return (EC_COMMAND_NOT_FOUND);
	// 	}
	// }
	// else
	// {
	// 	if (!ms_path_exist())
	// 	{
	// 		// No such file or directory
	// 		return (EC_COMMAND_NOT_FOUND);
	// 	}
	// }
	// if (ms_is_directory())
	// {
	// 	// is a directory
	// 	return (EC_COMMAND_NO_PERMISSION);
	// }
	// if (!ms_has_permission())
	// {
	// 	// Permission denied
	// 	return (EC_COMMAND_NO_PERMISSION);
	// }
	// // execve
	// // execute as shell script
	return (EC_COMMAND_NOT_FOUND);
}
