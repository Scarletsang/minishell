/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:56:31 by sawang            #+#    #+#             */
/*   Updated: 2023/06/09 20:28:53 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

int	ast_node_content_cmd_set(struct s_parser *parser, t_sb *cmd_word)
{
	if (sb_init(cmd_word, 10) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (sb_perform(cmd_word, \
	sb_action_append_len(parser->current_token->token.start, \
	parser->current_token->token.length)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_parser_exit_code	parse_cmd_word(struct s_parser *parser)
{
	t_sb	cmd_word;

	if (parser->malloc_fail == true)
		return (PARSER_FAILURE); //malloc fail
	if (parser->current_token->token.type != TOKEN_WORD)
		return (PARSER_FAILURE); //nothing to parse
	if (ast_node_content_cmd_set(parser, &cmd_word) == EXIT_FAILURE || \
	vector_append(&parser->current->content->command, &cmd_word) == \
	EXIT_FAILURE)
	{
		sb_free(&cmd_word);
		parser->malloc_fail = true;
		return (PARSER_FAILURE);
	}
	parser_token_advance(parser);
	return (PARSER_SUCCESS);
}

t_parser_exit_code	parse_cmd(struct s_parser *parser)
{
	apply the new rule
	// t_parser_exit_code	cmd_prefix_exit_code;
	// t_parser_exit_code	cmd_word_exit_code;
	// t_parser_exit_code	cmd_suffix_exit_code;

	// if (malloc_fail(parser) == true)
	// 	return (PARSER_FAILURE);
	// cmd_prefix_exit_code = parse_cmd_prefix(parser);
	// cmd_word_exit_code = parse_cmd_word(parser);
	// if (cmd_prefix_exit_code == PARSER_FAILURE && \
	// cmd_word_exit_code == PARSER_FAILURE)
	// 	return (PARSER_FAILURE);
	// if (cmd_prefix_exit_code == PARSER_SUCCESS && \
	// (parser->current_token->token.type == TOKEN_EOF || \
	// parser->current_token->token.type == TOKEN_PIPE))
	// 	return (PARSER_SUCCESS);
	// if (cmd_word_exit_code == PARSER_FAILURE)
	// 	return (PARSER_FAILURE);
	// cmd_suffix_exit_code = parse_cmd_suffix(parser);
	// if (cmd_suffix_exit_code == PARSER_FAILURE)
	// {
	// 	if (parser->current_token->token.type == TOKEN_EOF || \
	// 	parser->current_token->token.type == TOKEN_PIPE)
	// 		return (PARSER_SUCCESS);
	// 	return (PARSER_FAILURE);
	// }
}
