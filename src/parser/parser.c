/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:44:59 by sawang            #+#    #+#             */
/*   Updated: 2023/06/09 16:47:00 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

bool	parser_check_before_run(struct s_lexer *lexer, \
	t_lexer_exit_code lexer_exit_code)
{
	if (lexer_exit_code == ERROR_WHEN_LEX)
	{
		token_clear_when_lexer_failed(lexer, \
			(t_token_cleaner)del, "syntax error: unexpected end of file");
		return (EXIT_FAILURE);
	}
	if (lexer_exit_code == MALLOC_FAIL)
		return (EXIT_FAILURE);
	if (lexer_exit_code == NO_LINE)
		return (EXIT_FAILURE);
	// if (lexer_exit_code == LEXER_SUCCESS)
	// 	return (EXIT_SUCCESS);
	//should I check if it is empty token list at first and free the token list?
	// should I return success or failure in thsi case?
	// if (lexer->start->token.type == TOKEN_EOF)
	// {
	// 	token_clear_when_lexer_failed(lexer, \
	// 		(t_token_cleaner)del, NULL);
	// 	return (EXIT_FAILURE);
	// }
	return (EXIT_SUCCESS);
}

void	parser_init(struct s_parser *parser, struct s_token_list *start)
{
	parser->head = NULL;
	parser->current = NULL;
	parser->current_token = start;
	parser->start_token = start;
	parser->malloc_fail = false;
}

t_parser_exit_code	parse_complete_command(struct s_parser *parser)
{
	// parser->current = parser->head;
	if (parse_command(parser) == PARSER_FAILURE)
		return (PARSER_FAILURE);
	if (parse_pipe(parser) == PARSER_FAILURE)
		return (PARSER_SUCCESS);
	if (parse_complete_command(parser) == PARSER_FAILURE)
		return (PARSER_FAILURE); //syntax error
	return (PARSER_SUCCESS);
}
