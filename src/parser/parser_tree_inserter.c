/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree_inserter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:25:25 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 18:22:15 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser.h"

void	parser_ast_cmd_insert(struct s_parser *parser, \
struct s_ast_node *new_node)
{
	if (parser->head == NULL)
		parser->head = new_node;
	else if (parser->head->type == AST_NODE_PIPE)
		parser->head->right = new_node;
	parser->current = new_node;
}

void	parser_ast_pipe_insert(struct s_parser *parser, \
	struct s_ast_node *new_node)
{
	new_node->left = parser->head;
	parser->current = new_node;
	parser->head = parser->current;
}
