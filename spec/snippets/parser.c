/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 21:00:59 by htsang            #+#    #+#             */
/*   Updated: 2023/06/19 18:22:15 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/ast.h"
#include "MINISHELL/parser.h"
#include "MINISHELL/lexer/lexer.h"

int	parser_run(struct s_parser *parser)
{
	struct s_token_list	*token_head;

	token_head = parser->current_token;
	if (parser_something(parser))
	{
		ast_free(parser);
	}
	token_list_free(token_head);
}

int	parser_something(struct s_parser *parser)
{
	
}

int	content_add_assignment(struct s_AST_node_content *content, \
struct s_token *token)
{
	t_sb	sb;

	if (sb_init(&sb, 10))
		return (EXIT_FAILURE);
	if (sb_perform(&sb, sb_action_append_len(token->start, token->length)) || \
		vector_append(&content->assignment, &sb))
	{
		sb_free(&sb);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
