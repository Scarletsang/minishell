/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:44:59 by sawang            #+#    #+#             */
/*   Updated: 2023/06/21 15:09:58 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "LIBFT/string.h"
#include "MINISHELL/parser.h"

void	parser_init(struct s_parser *parser, struct s_token_list *start)
{
	parser->head = NULL;
	parser->current = NULL;
	parser->current_token = start;
	parser->malloc_fail = false;
}

void	token_clear_when_parser_finished(struct s_lexer *lexer, \
t_token_cleaner del)
{
	lexer_free(lexer, del);
}

t_ms_status	ast_parser_clear_when_failed(struct s_parser *parser, \
	char *err_message)
{
	if (ft_strcmp(err_message, "malloc fail") == 0)
		return (printf("%s\n", err_message), PROGRAM_ERROR);
	if (parser->current_token->token.type == TOKEN_EOF)
		printf("%s near unexpected token EOF\n", err_message);
	else
	{
		if (parser->current_token->token.type == TOKEN_GREAT || \
		parser->current_token->token.type == TOKEN_DGREAT || \
		parser->current_token->token.type == TOKEN_LESS || \
		parser->current_token->token.type == TOKEN_DLESS)
			parser_token_advance(parser);
		if (parser->current_token->token.type == TOKEN_EOF)
			printf("%s near unexpected token EOF\n", err_message);
		else
			printf("%s near unexpected token '%.*s'\n", err_message, \
			parser->current_token->token.length, \
			parser->current_token->token.start);
	}
	parser_free(parser);
	return (PROGRAM_FAILURE);
}

t_ms_status	parser_run(struct s_ast_node **ast_root, char *line)
{
	struct s_lexer		lexer;
	t_lexer_exit_code	lexer_exit_code;
	struct s_parser		parser;
	t_parser_exit_code	parser_exit_code;
	t_ms_status			prog_status;

	lexer_init(&lexer);
	lexer_exit_code = lexer_run(&lexer, line);
	if (lexer_exit_code == NO_LINE)
		return (EXIT_SUCCESS);
	if (lexer_exit_code != LEXER_SUCCESS)
		return (lexer_check_validation(&lexer, lexer_exit_code));
	parser_init(&parser, lexer.start);
	parser_exit_code = parse_complete_command(&parser);
	if (parser.malloc_fail == true)
		prog_status = ast_parser_clear_when_failed(&parser, "malloc fail");
	else if (parser_exit_code == PARSER_FAILURE)
		prog_status = ast_parser_clear_when_failed(&parser, "syntax error");
	else
	{
		*ast_root = parser.head;
		prog_status = PROGRAM_SUCCESS;
	}
	token_clear_when_parser_finished(&lexer, (t_token_cleaner)del);
	return (prog_status);
}
