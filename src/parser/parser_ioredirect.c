/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ioredirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:51:58 by sawang            #+#    #+#             */
/*   Updated: 2023/06/16 21:11:00 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

static t_ast_redirection_vector	*is_redirect_in_or_out(struct s_parser *parser, \
	struct s_ast_redirection io_file)
{
	if (io_file.type <= 1)
		return (&parser->current->content->redirection_in);
	else
		return (&parser->current->content->redirection_out);
}

// static t_parser_exit_code	ast_redirect_type_set(struct s_parser *parser, \
// 	struct s_ast_redirection *io_file)
// {
// 	if (parser->current_token->token.type == TOKEN_LESS)
// 		io_file->type = REDIRCT_STDIN;
// 	else if (parser->current_token->token.type == TOKEN_DLESS)
// 		io_file->type = REDIRECT_HEREDOC;
// 	else if (parser->current_token->token.type == TOKEN_GREAT)
// 		io_file->type = REDIRECT_STDOUT;
// 	else if (parser->current_token->token.type == TOKEN_DGREAT)
// 		io_file->type = REDIRECT_STDOUT_APPEND;
// 	else
// 		return (PARSER_FAILURE);
// 	return (PARSER_SUCCESS);
// }

// int	ast_redirect_content_set(struct s_parser *parser, \
// 	struct s_ast_redirection *io_file)
// {
// 	if (sb_init(&io_file->content, 10) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	if (sb_perform(&io_file->content, \
// 		sb_action_append_len(parser->current_token->token.start, \
// 		parser->current_token->token.length)) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

t_parser_exit_code	parse_io_redirect(struct s_parser *parser)
{
	struct s_ast_redirection	io_file;
	struct s_token_list			cur_tok;

	if (parser->malloc_fail == true)
		return (PARSER_FAILURE); //malloc fail
	cur_tok = parser_token_peek(parser);
	if (ast_redirect_type_set(parser->current_token->token.type, &io_file.type))
		return (PARSER_FAILURE); //syntax error
	if (parser_token_peek_next(parser).token.type != TOKEN_WORD && \
		parser_token_peek_next(parser).token.type != TOKEN_ASSIGNMENT_WORD)
		return (PARSER_FAILURE); //syntax error
	parser_token_advance(parser);
	if (ast_node_str_set(&io_file.content, parser->current_token->token.start, parser->current_token->token.length) == EXIT_FAILURE || \
		!vector_append(is_redirect_in_or_out(parser, io_file), &io_file))
	{
		sb_free(&io_file.content);
		parser->malloc_fail = true;
		return (PARSER_FAILURE); // malloc fail;
	}
	parser_token_advance(parser);
	return (PARSER_SUCCESS);
}
