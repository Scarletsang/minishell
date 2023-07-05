/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:49:02 by htsang            #+#    #+#             */
/*   Updated: 2023/07/05 23:09:01 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "MINISHELL/execution/command.h"
#include "LIBFT/string.h"
#include "LIBFT/io.h"
#include "LIBFT/iostream.h"

static t_ms_status	ms_execute_heredoc(\
struct s_ms_executor *executor, struct s_ast_redirection *redirection)
{
	int					read_status;
	t_ft_string_slice	slice;

	if ((ms_executor_redirection_in_file_open(executor, \
		HEREDOC_FILENAME, O_WRONLY | O_CREAT | O_TRUNC) == PROGRAM_ERROR))
		return (PROGRAM_ERROR);
	read_status = EXIT_SUCCESS;
	while (read_status == EXIT_SUCCESS)
	{
		ft_iostream_reset(&executor->stdin_stream);
		if (isatty(STDIN_FILENO))
			ft_putstr_fd("> ", STDOUT_FILENO);
		read_status = ft_iostream_read_until(&executor->stdin_stream, \
			STDIN_FILENO, (t_ft_string_slice){"\n", 1});
		slice = ft_iostream_to_slice(&executor->stdin_stream);
		if (slice.content == NULL)
			continue ;
		if (ft_strncmp(ft_string_slice_content(&slice), \
			redirection->content.buffer, slice.size - 1) == 0)
			return (ms_executor_redirect_from_heredoc(executor));
		ft_string_slice_print(slice, executor->redirection_in_fd);
	}
	if (ms_executor_redirect_from_heredoc(executor) == PROGRAM_ERROR)
		return (PROGRAM_ERROR);
	return (PROGRAM_FAILURE);
}

t_ms_status	ms_all_redirection_in_open(\
struct s_ms_executor *executor, t_ast_redirection_vector *redirection_in)
{
	t_ft_vector_iterator		iterator;
	struct s_ast_redirection	*redirection;
	t_ms_status					status;

	ft_vector_iterator_init(&iterator, redirection_in);
	while (!ft_vector_iterator_is_end(&iterator))
	{
		redirection = ft_vector_iterator_current(&iterator);
		if (redirection->type == REDIRECT_HEREDOC)
		{
			if (ms_execute_heredoc(executor, redirection) == PROGRAM_ERROR)
				return (PROGRAM_ERROR);
		}
		else if (redirection->type == REDIRCT_STDIN)
		{
			status = ms_executor_redirection_in_file_open(executor, \
				redirection->content.buffer, O_RDONLY);
			if (status != PROGRAM_SUCCESS)
				return (status);
		}
		ft_vector_iterator_next(&iterator);
	}
	return (PROGRAM_SUCCESS);
}

t_ms_status	ms_all_redirection_out_open(struct s_ms_executor *executor, \
t_ast_redirection_vector *redirection_out)
{
	t_ft_vector_iterator		iterator;
	struct s_ast_redirection	*redirection;
	int							flags;
	t_ms_status					status;

	ft_vector_iterator_init(&iterator, redirection_out);
	while (!ft_vector_iterator_is_end(&iterator))
	{
		redirection = ft_vector_iterator_current(&iterator);
		if (redirection->type == REDIRECT_STDOUT)
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		else if (redirection->type == REDIRECT_STDOUT_APPEND)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
		{
			ft_vector_iterator_next(&iterator);
			continue ;
		}
		status = ms_executor_redirection_out_file_open(executor, \
			redirection->content.buffer, flags);
		if (status != PROGRAM_SUCCESS)
			return (status);
		ft_vector_iterator_next(&iterator);
	}
	return (PROGRAM_SUCCESS);
}

t_ms_status	ms_all_redirection_in_out_open(struct s_ms_executor *executor, \
struct s_ast_node_content *content)
{
	t_ms_status	status;

	status = ms_all_redirection_in_open(executor, &content->redirection_in);
	if (status != PROGRAM_SUCCESS)
		return (status);
	status = ms_all_redirection_out_open(executor, &content->redirection_out);
	if (status != PROGRAM_SUCCESS)
		return (status);
	return (PROGRAM_SUCCESS);
}
