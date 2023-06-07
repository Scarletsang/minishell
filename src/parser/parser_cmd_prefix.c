/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_prefix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:38:51 by sawang            #+#    #+#             */
/*   Updated: 2023/06/07 22:23:29 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

// int parse_prefix(struct s_ast *ast, struct s_lexer *lexer)
// {
// 	int	parsed = EXIT_FAILURE;
// 	while (1)
// 	{
// 		if (!parse_io_redirect(ast, lexer))
// 		{
// 			parsed = EXIT_SUCCESS;
// 			continue;
// 		}
// 		if (!parse_assignment_word(ast, lexer))
// 		{
// 			parsed = EXIT_SUCCESS;
// 			continue;
// 		}
// 		break ;
// 	}
// 	return (parsed);
// }

int	ast_node_content_assignment_set(struct s_parser *parser)
{
	if (sb_init(&parser->current->content->assignment, 10) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (sb_perform(&parser->current->content->assignment, \
		sb_action_append_len(parser->current_token->token.start, \
		parser->current_token->token.length)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
t_parser_exit_code parse_assignment_word(struct s_parser *parser)
{
	// struct s_token_list	*cur_tok;
	struct s_sb_vector	

	if (parser->current_token->token.type != TOKEN_ASSIGNMENT_WORD)
		return (PARSER_FAILURE);
	if (ast_node_content_assignment_set(parser) == EXIT_FAILURE) || \
		vector_append(&parser->current->content->assignment, '\0') == EXIT_FAILURE)
		return (PARSER_SUCCESS);
}
t_parser_exit_code	parse_cmd_prefix(struct s_parser *parser)
{
	struct s_token_list	*start_tok;

	start_tok = parser->current_token;

	if (parse_io_redirect(parser) == PARSER_SUCCESS)
		return (PARSER_SUCCESS);
	if (parse_assignment_word(parser) == PARSER_SUCCESS)
		return (PARSER_SUCCESS);
}
