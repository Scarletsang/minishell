/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_prefix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:38:51 by sawang            #+#    #+#             */
/*   Updated: 2023/06/16 21:46:43 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

// int	ast_node_content_assignment_set(struct s_parser *parser, \
// 	t_sb *assignment)
// {
// 	if (sb_init(assignment, 10) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	if (sb_perform(assignment, \
// 	sb_action_append_len(parser->current_token->token.start, \
// 	parser->current_token->token.length)) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

t_parser_exit_code	parse_assignment_word(struct s_parser *parser)
{
	t_sb	assignment;

	if (parser->malloc_fail == true)
		return (PARSER_FAILURE); //malloc fail
	if (parser->current_token->token.type != TOKEN_ASSIGNMENT_WORD)
		return (PARSER_FAILURE); //nothing to parse
	if (ast_node_str_set(&assignment, parser->current_token->token.start, parser->current_token->token.length) == EXIT_FAILURE || \
		!vector_append(&parser->current->content->assignment, &assignment))
	{
		sb_free(&assignment);
		parser->malloc_fail = true;
		return (PARSER_FAILURE); //malloc fail
	}
	parser_token_advance(parser);
	return (PARSER_SUCCESS);
}

// t_parser_exit_code	parse_cmd_prefix(struct s_parser *parser)
// {
// 	struct s_token_list	*start_tok;

// 	start_tok = parser->current_token;
// 	if (parse_io_redirect(parser) == PARSER_SUCCESS)
// 		return (PARSER_SUCCESS);
// 	parser->current_token = start_tok;
// 	if (parse_assignment_word(parser) == PARSER_SUCCESS)
// 		return (PARSER_SUCCESS);
// }

t_parser_exit_code	parse_cmd_prefix(struct s_parser *parser)
{
	if (parser->malloc_fail == true)
		return (PARSER_FAILURE); //malloc fail
	if (parse_io_redirect(parser) == PARSER_SUCCESS)
	{
		parse_cmd_prefix(parser);
		return (PARSER_SUCCESS);
	}
	if (parse_assignment_word(parser) == PARSER_SUCCESS)
	{
		parse_cmd_prefix(parser);
		return (PARSER_SUCCESS);
	}
	return (PARSER_FAILURE); //nothing to p
}
