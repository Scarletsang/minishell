/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:20:29 by htsang            #+#    #+#             */
/*   Updated: 2023/06/24 03:34:46 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "MINISHELL/minishell.h"
#include "MINISHELL/parser.h"
#include "MINISHELL/execution.h"
#include "parser_tester.h"

extern char	**environ;

int	main(void)
{
	struct s_ms		ms;
	t_ms_exit_code	exit_code;

	if (ms_init(&ms) || \
		ms_vars_import(&ms.vars, environ))
	{
		ms_free(&ms);
		return (EXIT_FAILURE);
	}
	ms.line = readline("minishell$ ");
	exit_code = EC_SUCCESS;
	while (ms.line)
	{
		if (parser_run(&ms.ast_root, ms.line) == PROGRAM_SUCCESS)
		{
			add_history(ms.line);
			if (ms.ast_root)
			{
				exit_code = ms_execute_ast(&ms, ms.ast_root);
				print_ast(ms.ast_root);
			}
		}
		else
			exit_code = EC_SYNTAX_ERROR;
		// set exit code to special hashtable
		ms_reset(&ms);
		ms.line = readline("minishell$ ");
	}
	ms_free(&ms);
	return (exit_code);
}
