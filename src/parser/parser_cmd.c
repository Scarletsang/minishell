/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:56:31 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 18:28:55 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/parser.h"

t_parser_exit_code	parse_cmd_word(struct s_parser *parser)
{
	t_ft_sb	cmd_word;

	if (parser->malloc_fail == true)
		return (PARSER_FAILURE);
	if (parser->current_token->token.type != TOKEN_WORD)
		return (PARSER_FAILURE);
	if (ast_node_str_set(&cmd_word, parser->current_token->token.start, \
		parser->current_token->token.length) == EXIT_FAILURE || \
		!ft_vector_append(&parser->current->content->command, &cmd_word))
	{
		ft_sb_free(&cmd_word);
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
