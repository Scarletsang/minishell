/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:34:52 by htsang            #+#    #+#             */
/*   Updated: 2023/06/30 09:32:35 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "MINISHELL/execution/piper.h"

int	ms_piper_create_sender(struct s_ms_piper *piper)
{
	int	*sender_pipe;

	if (ms_piper_close_sender(piper))
		return (EXIT_FAILURE);
	sender_pipe = ms_piper_get_sender_pipe(piper);
	if (pipe(sender_pipe) == -1)
		return (EXIT_FAILURE);
	ms_piper_set_pipe_status(piper, sender_pipe, true);
	return (EXIT_SUCCESS);
}

int	ms_piper_close_sender(struct s_ms_piper *piper)
{
	int	*sender_pipe;
	int	exit_code;

	sender_pipe = ms_piper_get_sender_pipe(piper);
	exit_code = EXIT_SUCCESS;
	if (ms_piper_pipe_is_open(piper, sender_pipe))
	{
		if (ms_piper_close_pipe(sender_pipe))
			exit_code = EXIT_FAILURE;
		ms_piper_set_pipe_status(piper, sender_pipe, false);
	}
	return (exit_code);
}

int	ms_piper_use_sender(struct s_ms_piper *piper)
{
	int	*sender_pipe;
	int	exit_code;

	sender_pipe = ms_piper_get_sender_pipe(piper);
	exit_code = EXIT_SUCCESS;
	if (dup2(sender_pipe[1], STDOUT_FILENO) == -1)
		exit_code = EXIT_FAILURE;
	exit_code = ms_piper_close_sender(piper);
	return (exit_code);
}
