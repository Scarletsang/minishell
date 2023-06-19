/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_prefix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:38:51 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 18:29:30 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/parser.h"

t_parser_exit_code	parse_assignment_word(struct s_parser *parser)
{
	t_ft_sb	assignment;

	if (parser->malloc_fail == true)
		return (PARSER_FAILURE);
	if (parser->current_token->token.type != TOKEN_ASSIGNMENT_WORD)
		return (PARSER_FAILURE);
	if (ast_node_str_set(&assignment, parser->current_token->token.start, \
		parser->current_token->token.length) == EXIT_FAILURE || \
		!ft_vector_append(&parser->current->content->assignment, &assignment))
	{
		ft_sb_free(&assignment);
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
