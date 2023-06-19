/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree_inserter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:25:25 by sawang            #+#    #+#             */
/*   Updated: 2023/06/16 20:25:55 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

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
