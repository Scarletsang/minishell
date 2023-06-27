/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 02:33:24 by htsang            #+#    #+#             */
/*   Updated: 2023/06/26 02:38:54 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/general.h"
#include "MINISHELL/minishell.h"
#include "MINISHELL/parser.h"
#include "MINISHELL/execution.h"
#include "parser_tester.h"

t_ms_exit_code	ms_interpret(struct s_ms *ms, char *line)
{
	t_ms_exit_code	exit_code;

	if (parser_run(&ms->ast_root, line) == PROGRAM_SUCCESS)
	{
		exit_code = ms_execute_ast(ms, ms->ast_root);
		print_ast(ms->ast_root);
		return (exit_code);
	}
	else
		return (EC_SYNTAX_ERROR);
}

int	ms_exit_code_save(struct s_ms *ms, t_ms_exit_code exit_code)
{
	char	*num;

	num = ft_itoa(exit_code);
	if (!num)
		return (EXIT_FAILURE);
	if (ms_vars_database_set(&ms->vars.special, "?", num))
	{
		free(num);
		return (EXIT_FAILURE);
	}
	free(num);
	return (EXIT_SUCCESS);
}
