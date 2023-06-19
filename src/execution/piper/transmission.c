/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmission.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:34:52 by htsang            #+#    #+#             */
/*   Updated: 2023/06/19 16:46:53 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "MINISHELL/execution/piper.h"

int	ms_piper_create_sender(struct s_ms_piper *piper)
{
	int	*sender_pipe;

	sender_pipe = ms_piper_get_sender_pipe(piper);
	if (ms_piper_pipe_is_open(piper, sender_pipe))
	{
		if (ms_piper_close_pipe(sender_pipe))
			return (EXIT_FAILURE);
		ms_piper_set_pipe_status(piper, sender_pipe, false);
	}
	if (pipe(sender_pipe) == -1)
		return (EXIT_FAILURE);
	ms_piper_set_pipe_status(piper, sender_pipe, true);
	return (EXIT_SUCCESS);
}

void	ms_piper_create_receiver(struct s_ms_piper *piper)
{
	unsigned int	opened_pipes_count;

	opened_pipes_count = 0;
	if (piper->pipe1_opened)
		opened_pipes_count++;
	if (piper->pipe2_opened)
		opened_pipes_count++;
	if (opened_pipes_count == 0)
		piper->sender_is_pipe1 = true;
	else if (opened_pipes_count == 1)
		piper->sender_is_pipe1 = false;
	else
		piper->sender_is_pipe1 = !piper->sender_is_pipe1;
}

int	ms_piper_use_sender(struct s_ms_piper *piper)
{
	int	*sender_pipe;
	int	exit_code;

	sender_pipe = ms_piper_get_sender_pipe(piper);
	exit_code = EXIT_SUCCESS;
	if (dup2(sender_pipe[1], STDOUT_FILENO) == -1)
		exit_code = EXIT_FAILURE;
	if (ms_piper_close_pipe(sender_pipe))
		exit_code = EXIT_FAILURE;
	return (exit_code);
}

int	ms_piper_use_receiver(struct s_ms_piper *piper)
{
	int	*receiver_pipe;
	int	exit_code;

	receiver_pipe = ms_piper_get_receiver_pipe(piper);
	exit_code = EXIT_SUCCESS;
	if (dup2(receiver_pipe[0], STDOUT_FILENO) == -1)
		exit_code = EXIT_FAILURE;
	if (ms_piper_close_pipe(receiver_pipe))
		exit_code = EXIT_FAILURE;
	return (exit_code);
}
