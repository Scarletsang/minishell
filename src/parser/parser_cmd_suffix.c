/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_suffix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:10:29 by sawang            #+#    #+#             */
/*   Updated: 2023/06/09 16:57:38 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

int	ast_node_content_cmd_set(struct s_parser *parser, t_sb *cmd_parameter)
{
	if (sb_init(cmd_parameter, 10) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (sb_perform(cmd_parameter, \
	sb_action_append_len(parser->current_token->token.start, \
	parser->current_token->token.length)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_parser_exit_code	parse_cmd_parameter(struct s_parser *parser)
{
	t_sb	cmd_parameter;

	if (parser->malloc_fail == true)
		return (PARSER_FAILURE); //malloc fail
	if (parser->current_token->token.type != TOKEN_WORD && \
	parser->current_token->token.type != TOKEN_ASSIGNMENT_WORD)
		return (PARSER_FAILURE); //nothing to parse
	if (ast_node_content_cmd_set(parser, &cmd_parameter) == EXIT_FAILURE || \
	vector_append(&parser->current->content->command, &cmd_parameter) == \
	EXIT_FAILURE)
	{
		sb_free(&cmd_parameter);
		parser->malloc_fail = true;
		return (PARSER_FAILURE);
	}
	parser_token_advance(parser);
	return (PARSER_SUCCESS);
}

t_parser_exit_code	parse_cmd_suffix(struct s_parser *parser)
{
	if (malloc_fail(parser) == true)
		return (PARSER_FAILURE);
	if (parse_io_redirect(parser) == PARSER_SUCCESS)
	{
		parse_cmd_suffix(parser);
		return (PARSER_SUCCESS);
	}
	if (parse_wordlist(parser) == PARSER_SUCCESS)
	{
		parse_cmd_suffix(parser);
		return (PARSER_SUCCESS);
	}
	return (PARSER_FAILURE);
}
