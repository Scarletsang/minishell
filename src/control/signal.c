/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:21:32 by htsang            #+#    #+#             */
/*   Updated: 2023/06/29 17:09:41 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include "MINISHELL/minishell.h"
#include "MINISHELL/status_code.h"

volatile t_ms_exit_code	g_exit_code;

void	ms_sigint_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	write(STDOUT_FILENO, "\nminishell$ ", 12);
	g_exit_code = EC_FAILURE;
}

int	ms_signal_handlers_set(void)
{
	struct sigaction	sigact;

	sigact.sa_flags = SA_RESTART;
	sigact.sa_handler = &ms_sigint_handler;
	sigaction(SIGINT, &sigact, NULL);
	sigact.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigact, NULL);
	sigaction(SIGTSTP, &sigact, NULL);
	return (EXIT_SUCCESS);
}
