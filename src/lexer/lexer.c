/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:11:34 by sawang            #+#    #+#             */
/*   Updated: 2023/06/25 04:42:05 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "MINISHELL/lexer.h"
#include "MINISHELL/error_printer.h"

void	lexer_init(struct s_lexer *lexer)
{
	lexer->start = NULL;
	lexer->end = NULL;
}

t_lexer_exit_code	lexer_run(struct s_lexer *lexer, char *line)
{
	struct s_scanner	scanner;
	struct s_token		token;
	struct s_token_list	*token_lst;

	scanner_init(&scanner, line);
	while (1)
	{
		token = token_scan(&scanner);
		token_lst = token_new(token);
		if (!token_lst)
			return (MALLOC_FAIL);
		token_add_back(lexer, token_lst);
		if (token.type == TOKEN_ERROR)
			return (ERROR_WHEN_LEX);
		if (token.type == TOKEN_EOF)
			break ;
	}
	token_lstitr_update_assignmentword(lexer->start, \
		(t_token_updater)token_update);
	return (LEXER_SUCCESS);
}

t_ms_status	lexer_check_validation(struct s_lexer *lexer, \
	t_lexer_exit_code lexer_exit_code)
{
	if (lexer_exit_code == ERROR_WHEN_LEX)
	{
		ms_error_printer_lexer(lexer->end->token.start);
		lexer_free(lexer, (t_token_cleaner)del);
		return (PROGRAM_FAILURE);
	}
	if (lexer_exit_code == MALLOC_FAIL)
	{
		lexer_free(lexer, (t_token_cleaner)del);
		ms_error_printer_internal_error();
		return (PROGRAM_ERROR);
	}
	return (PROGRAM_SUCCESS);
}
