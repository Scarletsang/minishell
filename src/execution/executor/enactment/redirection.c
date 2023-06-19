/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:49:02 by htsang            #+#    #+#             */
/*   Updated: 2023/06/19 18:39:32 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "MINISHELL/execution/executor/enactment.h"
#include "LIBFT/iostream.h"

static t_executor_exit_code	ms_executor_enact_heredoc(\
struct s_ms_executor *executor, struct s_ast_redirection *redirection)
{
	struct s_ft_iostream	iostream;
	t_ft_string_slice		slice;

	if (!executor->heredoc_fd_opened)
	{
		executor->heredoc_fd = open(HEREDOC_FILENAME, O_WRONLY | O_CREAT | \
			O_TRUNC, 0644);
		if (executor->heredoc_fd < 0)
			return (EXECUTION_ERROR);
		executor->heredoc_fd_opened = true;
	}
	if (ft_sb_perform(&redirection->content, ft_sb_action_append("\n")) || \
		ft_iostream_init(&iostream))
		return (EXECUTION_ERROR);
	if (ft_iostream_read_until(&iostream, executor->stdin_fd, \
		redirection->content.buffer) == -1)
		return (EXECUTION_ERROR);
	slice = ft_iostream_to_slice(&iostream);
	if (write(executor->heredoc_fd, slice.content, slice.size) < 0)
		return (EXECUTION_ERROR);
	ft_iostream_free(&iostream);
	return (EXECUTION_SUCCESS);
}

t_executor_exit_code	ms_executor_enact_redirection_in(\
struct s_ms_executor *executor, t_ast_redirection_vector *redirection_in)
{
	t_ft_vector_iterator		iterator;
	struct s_ast_redirection	*redirection;

	ft_vector_iterator_init(&iterator, redirection_in);
	while (!ft_vector_iterator_is_end(&iterator))
	{
		redirection = ft_vector_iterator_current(&iterator);
		if (redirection->type == REDIRECT_HEREDOC)
		{
			if (ms_executor_enact_heredoc(executor, redirection) \
				== EXECUTION_ERROR)
				return (EXECUTION_ERROR);
		}
		else if (redirection->type == REDIRCT_STDIN)
		{
			if (ms_executor_read_from_fd(open(\
				redirection->content.buffer, O_RDONLY)) == EXECUTION_ERROR)
				return (EXECUTION_ERROR);
		}
		ft_vector_iterator_next(&iterator);
	}
	return (EXECUTION_SUCCESS);
}

t_executor_exit_code	ms_executor_enact_redirection_out(\
t_ast_redirection_vector *redirection_out)
{
	t_ft_vector_iterator		iterator;
	struct s_ast_redirection	*redirection;

	ft_vector_iterator_init(&iterator, redirection_out);
	while (!ft_vector_iterator_is_end(&iterator))
	{
		redirection = ft_vector_iterator_current(&iterator);
		if (redirection->type == REDIRECT_STDOUT)
		{
			if (ms_executor_write_to_fd(\
					open(redirection->content.buffer, \
					O_WRONLY | O_CREAT | O_TRUNC, 0644)) == EXECUTION_ERROR)
				return (EXECUTION_ERROR);
		}
		else if (redirection->type == REDIRECT_STDOUT_APPEND)
		{
			if (ms_executor_write_to_fd(\
					open(redirection->content.buffer, \
					O_WRONLY | O_CREAT | O_APPEND, 0644)) == EXECUTION_ERROR)
				return (EXECUTION_ERROR);
		}
		ft_vector_iterator_next(&iterator);
	}
	return (EXECUTION_SUCCESS);
}
