/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:19:47 by htsang            #+#    #+#             */
/*   Updated: 2023/06/28 11:47:34 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/command/external.h"

t_ms_status	ms_execve_builder_init(struct s_ms_execve_builder *executable)
{
	executable->argv = NULL;
	return (ft_sb_init(&executable->path, 20));
}

void	ms_execve_builder_free(struct s_ms_execve_builder *executable)
{
	if (executable->argv)
		free(executable->argv);
	ft_sb_free(&executable->path);
}

t_ms_status	ms_execve_builder_path_build(\
struct s_ms_execve_builder *executable, struct s_ms *ms, t_ft_sb *command_name)
{
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
}

bool	ms_execve_builder_path_is_executable(\
struct s_ms_execve_builder *executable)
{
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
}

t_ms_status	ms_execve_builder_argv_build(\
struct s_ms_execve_builder *executable, t_sb_vector *command)
{
	t_ft_vector_iterator	iterator;
	size_t					i;

	executable->argv = malloc(sizeof(char *) * command->size + 1);
	if (!executable)
		return (PROGRAM_ERROR);
	executable->argv[command->size] = NULL;
	i = 0;
	ft_vector_iterator_init(&iterator, command);
	while (!ft_vector_iterator_is_end(&iterator))
	{
		executable->argv[i] = (char *) \
			((t_ft_sb *) ft_vector_iterator_current(&iterator))->buffer;
		ft_vector_iterator_next(&iterator);
	}
	return (PROGRAM_SUCCESS);
}
