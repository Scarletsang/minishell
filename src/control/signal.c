/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:21:32 by htsang            #+#    #+#             */
/*   Updated: 2023/07/05 14:34:36 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include "MINISHELL/minishell.h"
#include "MINISHELL/status_code.h"

volatile t_ms_exit_code	g_exit_code;

void	ms_signal_handler_interative(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	write(STDOUT_FILENO, "\nminishell$ ", 12);
	g_exit_code = EC_FAILURE;
}

void	ms_signal_handler_foreground_command(int signum)
{
	g_exit_code = ms_exit_code_from_signal(signum);
}

int	ms_signal_handlers_interactive_set(void)
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_RESTART;
	sigact.sa_handler = &ms_signal_handler_interative;
	sigaction(SIGINT, &sigact, NULL);
	sigact.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigact, NULL);
	sigaction(SIGTSTP, &sigact, NULL);
	return (EXIT_SUCCESS);
}

int	ms_signal_handlers_foreground_command_set(void)
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_RESTART;
	sigact.sa_handler = &ms_signal_handler_foreground_command;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
	sigaction(SIGTSTP, &sigact, NULL);
	return (EXIT_SUCCESS);
}
