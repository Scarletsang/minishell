/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:29:00 by htsang            #+#    #+#             */
/*   Updated: 2023/06/19 16:46:48 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/execution/piper.h"

void	ms_piper_init(struct s_ms_piper *piper)
{
	piper->sender_is_pipe1 = true;
	piper->pipe1_opened = false;
	piper->pipe2_opened = false;
}

int	ms_piper_destroy(struct s_ms_piper *piper)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (piper->pipe1_opened && (ms_piper_close_pipe(piper->pipe1) \
		== EXIT_FAILURE))
		exit_code = EXIT_FAILURE;
	if (piper->pipe2_opened && (ms_piper_close_pipe(piper->pipe2) \
		== EXIT_FAILURE))
		exit_code = EXIT_FAILURE;
	return (exit_code);
}
