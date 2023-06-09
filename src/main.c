/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:20:29 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 05:06:22 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "MINISHELL/minishell.h"
#include "MINISHELL/status_code.h"
#include "MINISHELL/error_printer.h"

static int	ms_non_interactive_mode(void)
{
	struct s_ms				ms;
	t_ms_exit_code			exit_code;
	int						iostream_read_status;

	if (ms_init(&ms))
		return (ms_free(&ms), EXIT_FAILURE);
	exit_code = EC_SUCCESS;
	iostream_read_status = EXIT_SUCCESS;
	while (iostream_read_status == EXIT_SUCCESS)
	{
		iostream_read_status = ft_iostream_read_until_delimiter(\
			&ms.executor.stdin_stream, STDIN_FILENO, \
			(t_ft_str){"\n", 1});
		ms.line = ft_str_to_cstring(ft_iostream_to_slice(\
			&ms.executor.stdin_stream));
		if ((ms.line != NULL) && !ms_line_is_empty(ms.line))
		{
			exit_code = ms_interpret(&ms, ms.line);
			ms_exit_code_save(&ms, exit_code);
		}
		ms_reset(&ms);
	}
	ms_free(&ms);
	return (exit_code);
}

static int	ms_non_interactive_mode_from_path(const char *path)
{
	t_ms_exit_code	exit_code;
	int				fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ms_exit_code_evaluate(path, true, true));
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		exit_code = ms_non_interactive_mode();
	}
	return (exit_code);
}

static int	ms_interactive_mode(char *prompt)
{
	struct s_ms		ms;
	t_ms_exit_code	exit_code;

	if (ms_init(&ms))
		return (ms_free(&ms), EXIT_FAILURE);
	ms.line = readline(prompt);
	exit_code = EC_SUCCESS;
	while (ms.line)
	{
		if (ms.line[0] != '\0')
		{
			add_history(ms.line);
			if (!ms_line_is_empty(ms.line))
			{
				ms_signal_handlers_foreground_command_set();
				exit_code = ms_interpret(&ms, ms.line);
				ms_exit_code_save(&ms, exit_code);
				ms_signal_handlers_interactive_set();
			}
		}
		ms_exit_code_save_from_signal(&ms);
		ms_reset(&ms);
		ms.line = readline(prompt);
	}
	return (ms_free(&ms), exit_code);
}

int	main(int argc, char **argv)
{
	t_ms_exit_code	exit_code;

	if (argc >= 2)
	{
		exit_code = ms_non_interactive_mode_from_path(argv[1]);
	}
	else if (isatty(STDIN_FILENO))
	{
		ms_terminal_settings_change();
		ms_signal_handlers_interactive_set();
		exit_code = ms_interactive_mode("minishell$ ");
		ms_terminal_settings_restore();
	}
	else
		exit_code = ms_non_interactive_mode();
	return (exit_code);
}
