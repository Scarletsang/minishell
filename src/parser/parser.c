/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:44:59 by sawang            #+#    #+#             */
/*   Updated: 2023/06/17 17:41:32 by sawang           ###   ########.fr       */
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
	parser->malloc_fail = false;
}

static void	token_clear_when_parser_finished(struct s_lexer *lexer, \
t_token_cleaner del, char *err_message)
{
	token_clear_when_lexer_failed(lexer, del, err_message);
}

struct s_ast_node	*ast_parser_clear_when_failed(struct s_parser *parser, \
	char *err_message)
{
	printf("%s at '%.*s'\n", err_message, parser->current_token->token.length, \
		parser->current_token->token.start);
	parser_free(parser);
	return (NULL);
}

struct s_ast_node	*parser_run(char *line)
{
	struct s_lexer		lexer;
	t_lexer_exit_code	lexer_exit_code;
	struct s_parser		parser;
	t_parser_exit_code	parser_exit_code;
	struct s_ast_node	*ast_root;

	lexer_init(&lexer);
	lexer_exit_code = token_list_get(&lexer, line);
	if (parser_check_before_run(&lexer, lexer_exit_code) == EXIT_FAILURE)
		return (NULL);
	parser_init(&parser, lexer.start);
	parser_exit_code = parse_complete_command(&parser);
	if (parser.malloc_fail == true)
		ast_root = ast_parser_clear_when_failed(&parser, "malloc fail");
	else if (parser_exit_code == PARSER_FAILURE)
		ast_root = ast_parser_clear_when_failed(&parser, "syntax error");
	else
		ast_root = parser.head;
	token_clear_when_parser_finished(&lexer, (t_token_cleaner)del, NULL);
	return (ast_root);
}
