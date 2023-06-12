/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:55:35 by htsang            #+#    #+#             */
/*   Updated: 2023/06/11 16:43:50 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor/piper.h"

int	*ms_piper_get_sender_pipe(struct s_ms_piper *piper)
{
	if (piper->sender_is_pipe1)
		return (piper->pipe1);
	else
		return (piper->pipe2);
}

int	*ms_piper_get_receiver_pipe(struct s_ms_piper *piper)
{
	if (piper->sender_is_pipe1)
		return (piper->pipe2);
	else
		return (piper->pipe1);
}

bool	ms_piper_pipe_is_open(struct s_ms_piper *piper, int *pipe)
{
	if (pipe == piper->pipe1)
		return (piper->pipe1_opened);
	else if (pipe == piper->pipe2)
		return (piper->pipe2_opened);
	return (false);
}

int	ms_piper_set_pipe_status(struct s_ms_piper *piper, int *pipe, bool piped)
{
	if (pipe == piper->pipe1)
		piper->pipe1_opened = piped;
	else if (pipe == piper->pipe2)
		piper->pipe2_opened = piped;
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ms_piper_close_pipe(int *pipe)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (close(pipe[0]) == -1)
		exit_code = EXIT_FAILURE;
	if (close(pipe[1]) == -1)
		exit_code = EXIT_FAILURE;
	return (exit_code);
}
