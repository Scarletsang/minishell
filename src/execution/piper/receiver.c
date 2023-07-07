/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receiver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:34:52 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 04:07:44 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "MINISHELL/execution/piper.h"

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
	else
		piper->sender_is_pipe1 = !piper->sender_is_pipe1;
}

int	ms_piper_close_receiver(struct s_ms_piper *piper)
{
	int	*receiver_pipe;
	int	exit_code;

	receiver_pipe = ms_piper_get_receiver_pipe(piper);
	exit_code = EXIT_SUCCESS;
	if (ms_piper_pipe_is_open(piper, receiver_pipe))
	{
		if (ms_piper_close_pipe(receiver_pipe))
			exit_code = EXIT_FAILURE;
		ms_piper_set_pipe_status(piper, receiver_pipe, false);
	}
	return (exit_code);
}

int	ms_piper_use_receiver(struct s_ms_piper *piper)
{
	int	*receiver_pipe;
	int	exit_code;

	receiver_pipe = ms_piper_get_receiver_pipe(piper);
	exit_code = EXIT_SUCCESS;
	if (dup2(receiver_pipe[0], STDIN_FILENO) == -1)
		exit_code = EXIT_FAILURE;
	exit_code = ms_piper_close_receiver(piper);
	return (exit_code);
}
