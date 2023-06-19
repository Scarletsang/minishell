/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ioredirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:51:58 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 18:34:44 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/parser.h"

static t_ast_redirection_vector	*is_redirect_in_or_out(struct s_parser *parser, \
	struct s_ast_redirection io_file)
{
	if (io_file.type <= 1)
		return (&parser->current->content->redirection_in);
	else
		return (&parser->current->content->redirection_out);
}

t_parser_exit_code	parse_io_redirect(struct s_parser *parser)
{
	struct s_ast_redirection	io_file;
	struct s_token_list			cur_tok;

	if (parser->malloc_fail == true)
		return (PARSER_FAILURE);
	cur_tok = parser_token_peek(parser);
	if (ast_redirect_type_set(parser->current_token->token.type, &io_file.type))
		return (PARSER_FAILURE);
	if (parser_token_peek_next(parser).token.type != TOKEN_WORD && \
		parser_token_peek_next(parser).token.type != TOKEN_ASSIGNMENT_WORD)
		return (PARSER_FAILURE);
	parser_token_advance(parser);
	if (ast_node_str_set(&io_file.content, parser->current_token->token.start, \
	parser->current_token->token.length) == EXIT_FAILURE || \
		!ft_vector_append(is_redirect_in_or_out(parser, io_file), &io_file))
	{
		ft_sb_free(&io_file.content);
		parser->malloc_fail = true;
		return (PARSER_FAILURE);
	}
	parser_token_advance(parser);
	return (PARSER_SUCCESS);
}
