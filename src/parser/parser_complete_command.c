/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_complete_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:13:19 by sawang            #+#    #+#             */
/*   Updated: 2023/06/16 20:17:30 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

t_parser_exit_code	parse_pipe(struct s_parser *parser)
{
	struct s_ast_node	*new_node;

	if (parser->malloc_fail == true)
		return (PARSER_FAILURE);
	if (parser->current_token->token.type != TOKEN_PIPE)
		return (PARSER_FAILURE); //syntax error
	new_node = ast_node_pipe_create();
	if (!new_node)
	{
		parser->malloc_fail = true;
		return (PARSER_FAILURE);
	}
	parser_ast_pipe_insert(parser, new_node);
	parser_token_advance(parser);
	return (PARSER_SUCCESS);
}

t_parser_exit_code	parse_eof(struct s_parser *parser)
{
	if (parser->malloc_fail == true)
		return (PARSER_FAILURE);
	if (parser->current_token->token.type != TOKEN_EOF)
		return (PARSER_FAILURE); //syntax error
	return (PARSER_SUCCESS);
}

//in parse_complete_command, update the head of parser??
t_parser_exit_code	parse_complete_command(struct s_parser *parser)
{
	if (parser->malloc_fail == true)
		return (PARSER_FAILURE);
	if (parse_cmd(parser) == PARSER_FAILURE)
		return (PARSER_FAILURE);
	if (parse_eof(parser) == PARSER_SUCCESS)
		return (PARSER_SUCCESS);
	if (parse_pipe(parser) == PARSER_FAILURE)
		return (PARSER_FAILURE);
	if (parse_complete_command(parser) == PARSER_FAILURE)
		return (PARSER_FAILURE); //syntax error
	return (PARSER_SUCCESS); //no single token to parse, only eof
}
