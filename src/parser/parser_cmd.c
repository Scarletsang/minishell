/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:56:31 by sawang            #+#    #+#             */
/*   Updated: 2023/06/16 20:06:48 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

// int	ast_node_content_cmd_set(struct s_parser *parser, t_sb *cmd_word)
// {
// 	if (sb_init(cmd_word, 10) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	if (sb_perform(cmd_word, \
// 	sb_action_append_len(parser->current_token->token.start, \
// 	parser->current_token->token.length)) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

t_parser_exit_code	parse_cmd_word(struct s_parser *parser)
{
	t_sb	cmd_word;

	if (parser->malloc_fail == true)
		return (PARSER_FAILURE); //malloc fail
	if (parser->current_token->token.type != TOKEN_WORD)
		return (PARSER_FAILURE); //syntax error
	if (ast_node_str_set(&cmd_word, parser->current_token->token.start, parser->current_token->token.length) == EXIT_FAILURE || \
		!vector_append(&parser->current->content->command, &cmd_word))
	{
		sb_free(&cmd_word);
		parser->malloc_fail = true;
		return (PARSER_FAILURE);
	}
	parser_token_advance(parser);
	return (PARSER_SUCCESS);
}

//in parse_cmd, create the new node and save it in parser->current
t_parser_exit_code	parse_cmd(struct s_parser *parser)
{
	struct s_ast_node	*new_node;

	if (parser->malloc_fail == true)
		return (PARSER_FAILURE);
	new_node = ast_node_cmd_create();
	if (!new_node)
	{
		parser->malloc_fail = true;
		return (PARSER_FAILURE);
	}
	parser_ast_cmd_insert(parser, new_node);
	if (parse_cmd_prefix(parser) == PARSER_FAILURE)
	{
		if (parse_cmd_word(parser) == PARSER_FAILURE)
			// return (free(new_node), PARSER_FAILURE); //syntax error
			return (PARSER_FAILURE);
	}
	else
	{
		if (parse_cmd_word(parser) == PARSER_FAILURE)
			return (PARSER_SUCCESS);
	}
	parse_cmd_suffix(parser);
	return (PARSER_SUCCESS);
}