/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:19:47 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 01:02:57 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/command/external.h"

t_ms_status	ms_execve_builder_init(struct s_ms_execve_builder *builder, \
struct s_ms *ms, t_sb_vector *command)
{
	builder->argv = NULL;
	builder->path_env = ms_executor_envp_get(&ms->executor, "PATH=");
	if (builder->path_env != NULL)
	{
		while (*builder->path_env && (*builder->path_env != '='))
			builder->path_env++;
		if (*(builder->path_env + 1) == '\0')
			builder->path_env = NULL;
	}
	if (command->size == 0)
		builder->command_name = NULL;
	else
		builder->command_name = ft_vector_get(command, 0);
	if (ft_sb_init(&builder->command_path, 20))
		return (PROGRAM_ERROR);
	return (PROGRAM_SUCCESS);
}

void	ms_execve_builder_free(struct s_ms_execve_builder *builder)
{
	if (builder->argv)
		free(builder->argv);
	if (builder->command_path.buffer != builder->command_name->buffer)
		ft_sb_free(&builder->command_path);
}

t_ms_exit_code	ms_execve_builder_path_build(\
struct s_ms_execve_builder *builder)
{
	const char		*path;
	size_t			path_len;
	t_ms_exit_code	exit_code;

	path = builder->path_env;
	exit_code = EC_SUCCESS;
	while (*path++)
	{
		ft_sb_reset(&builder->command_path);
		path_len = 0;
		while (path[path_len] && (path[path_len] != ':'))
			path_len++;
		if (ft_sb_perform(&builder->command_path, ft_sb_action_append_len(\
				path, path_len)) || \
			ft_sb_perform(&builder->command_path, ft_sb_action_append("/")) || \
			ft_sb_perform(&builder->command_path, ft_sb_action_append_len(\
				builder->command_name->buffer, builder->command_name->size)))
			return (__EC_INTERNAL_ERROR);
		exit_code = ms_exit_code_evaluate(\
			builder->command_path.buffer, false, false);
		if (exit_code == EC_SUCCESS)
			return (EC_SUCCESS);
		path += path_len;
	}
	return (exit_code);
}

t_ms_status	ms_execve_builder_argv_build(\
struct s_ms_execve_builder *builder, t_sb_vector *command)
{
	t_ft_vector_iterator	iterator;
	size_t					i;

	builder->argv = malloc(sizeof(char *) * (command->size + 1));
	if (!builder)
		return (PROGRAM_ERROR);
	(builder->argv)[command->size] = NULL;
	i = 0;
	ft_vector_iterator_init(&iterator, command);
	while (!iterator.is_end)
	{
		builder->argv[i] = (char *) \
			((t_ft_sb *) ft_vector_iterator_current(&iterator))->buffer;
		ft_vector_iterator_next(&iterator);
		i++;
	}
	return (PROGRAM_SUCCESS);
}
