/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_prefix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:38:51 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 15:51:41 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

t_parser_exit_code	parse_assignment_word(struct s_parser *parser)
{
	t_sb	assignment;

	if (parser->malloc_fail == true)
		return (PARSER_FAILURE);
	if (parser->current_token->token.type != TOKEN_ASSIGNMENT_WORD)
		return (PARSER_FAILURE);
	if (ast_node_str_set(&assignment, parser->current_token->token.start, \
		parser->current_token->token.length) == EXIT_FAILURE || \
		!vector_append(&parser->current->content->assignment, &assignment))
	{
		sb_free(&assignment);
		parser->malloc_fail = true;
		return (PARSER_FAILURE);
	}
	parser_token_advance(parser);
	return (PARSER_SUCCESS);
}

t_parser_exit_code	parse_cmd_prefix(struct s_parser *parser)
{
	if (parser->malloc_fail == true)
		return (PARSER_FAILURE);
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
	return (PARSER_FAILURE);
}
