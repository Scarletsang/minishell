/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:19:47 by htsang            #+#    #+#             */
/*   Updated: 2023/06/28 21:55:46 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/command/external.h"

t_ms_status	ms_execve_builder_init(struct s_ms_execve_builder *builder, \
struct s_ms *ms, t_sb_vector *command)
{
	builder->argv = NULL;
	builder->path_env = ms_vars_echo(&ms->vars, "PATH");
	while (*builder->path_env && (*builder->path_env != '='))
		builder->path_env++;
	builder->command_name = ft_vector_get(command, 0);
	builder->exit_code = EC_SUCCESS;
	return (ft_sb_init(&builder->command_path, 20));
}

void	ms_execve_builder_free(struct s_ms_execve_builder *builder)
{
	if (builder->argv)
		free(builder->argv);
	ft_sb_free(&builder->command_path);
}

t_ms_status	ms_execve_builder_path_build(struct s_ms_execve_builder *builder)
{
	const char		*path;
	size_t			path_len;

	path = builder->path_env;
	while (*path)
	{
		path++;
		ft_sb_reset(&builder->command_path);
		path_len = 0;
		while (path[path_len] && (path[path_len] != ':'))
			path_len++;
		if (ft_sb_perform(&builder->command_path, \
				ft_sb_action_append_len(path, path_len)) || \
			ft_sb_perform(&builder->command_path, \
				ft_sb_action_append("/")) || \
			ft_sb_perform(&builder->command_path, \
				ft_sb_action_append_len(builder->command_name->buffer, \
				builder->command_name->size)))
			return (PROGRAM_ERROR);
		ms_execve_builder_command_path_exit_code_get(builder);
		if (builder->exit_code == EC_SUCCESS)
			return (PROGRAM_SUCCESS);
		path += path_len;
	}
	return (PROGRAM_FAILURE);
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
	while (!ft_vector_iterator_is_end(&iterator))
	{
		builder->argv[i] = (char *) \
			((t_ft_sb *) ft_vector_iterator_current(&iterator))->buffer;
		ft_vector_iterator_next(&iterator);
		i++;
	}
	return (PROGRAM_SUCCESS);
}
