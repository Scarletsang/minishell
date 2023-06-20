/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_suffix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:10:29 by sawang            #+#    #+#             */
/*   Updated: 2023/06/20 15:26:40 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/parser.h"

t_parser_exit_code	parse_cmd_parameter(struct s_parser *parser)
{
	t_ft_sb	cmd_parameter;

	if (parser->malloc_fail == true)
		return (PARSER_FAILURE);
	if (parser->current_token->token.type != TOKEN_WORD && \
	parser->current_token->token.type != TOKEN_ASSIGNMENT_WORD)
		return (PARSER_FAILURE);
	if (ast_node_str_set(&cmd_parameter, parser->current_token->token.start, \
		parser->current_token->token.length) == EXIT_FAILURE || \
		!ft_vector_append(&parser->current->content->command, &cmd_parameter))
	{
		ft_sb_free(&cmd_parameter);
		parser->malloc_fail = true;
		return (PARSER_FAILURE);
	}
	parser_token_advance(parser);
	return (PARSER_SUCCESS);
}

t_parser_exit_code	parse_cmd_suffix(struct s_parser *parser)
{
	if (parser->malloc_fail == true)
		return (PARSER_FAILURE);
	if (parse_io_redirect(parser) == PARSER_SUCCESS)
	{
		parse_cmd_suffix(parser);
		return (PARSER_SUCCESS);
	}
	if (parse_cmd_parameter(parser) == PARSER_SUCCESS)
	{
		parse_cmd_suffix(parser);
		return (PARSER_SUCCESS);
	}
	return (PARSER_FAILURE);
}
