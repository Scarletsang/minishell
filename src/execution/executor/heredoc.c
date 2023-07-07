/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:50:34 by htsang            #+#    #+#             */
/*   Updated: 2023/07/05 20:39:49 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "MINISHELL/execution/executor.h"

t_ms_status	ms_executor_redirect_from_heredoc(struct s_ms_executor *executor)
{
	if (close(executor->redirection_in_fd) == -1)
		return (PROGRAM_ERROR);
	executor->redirection_in_fd = open(HEREDOC_FILENAME, O_RDONLY, 0644);
	if (executor->redirection_in_fd == -1)
		return (PROGRAM_ERROR);
	if (unlink(HEREDOC_FILENAME) == -1)
		return (PROGRAM_ERROR);
	return (PROGRAM_SUCCESS);
}
