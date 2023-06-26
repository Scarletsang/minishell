/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:20:29 by htsang            #+#    #+#             */
/*   Updated: 2023/06/26 02:37:32 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "MINISHELL/minishell.h"

int	ms_non_interactive_mode(int fd)
{
	struct s_ms				ms;
	struct s_ft_iostream	iostream;
	t_ms_exit_code			exit_code;
	int						iostream_read_status;

	if (ms_init(&ms) || ft_iostream_init(&iostream))
		return (ms_free(&ms), EXIT_FAILURE);
	exit_code = EC_SUCCESS;
	iostream_read_status = EXIT_SUCCESS;
	while (iostream_read_status == EXIT_SUCCESS)
	{
		iostream_read_status = ft_iostream_read_until_delimiter(&iostream, fd, \
			(t_ft_string_slice){"\n", 1});
		ms.line = ft_string_slice_to_cstring(ft_iostream_to_slice(&iostream));
		if ((ms.line != NULL) && !ms_line_is_empty(ms.line))
		{
			exit_code = ms_interpret(&ms, ms.line);
			ms_exit_code_save(&ms, exit_code);
		}
		ft_iostream_reset(&iostream);
		ms_reset(&ms);
	}
	ms_free(&ms);
	ft_iostream_free(&iostream);
	return (exit_code);
}

int	ms_interactive_mode(char *prompt)
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
				exit_code = ms_interpret(&ms, ms.line);
				ms_exit_code_save(&ms, exit_code);
			}
		}
		ms_reset(&ms);
		ms.line = readline(prompt);
	}
	ms_free(&ms);
	return (exit_code);
}

int	main(void)
{
	t_ms_exit_code	exit_code;

	if (isatty(STDIN_FILENO))
	{
		ms_terminal_settings_change();
		exit_code = ms_interactive_mode("minishell$ ");
		ms_terminal_settings_restore();
	}
	else
		exit_code = ms_non_interactive_mode(STDIN_FILENO);
	return (exit_code);
}
