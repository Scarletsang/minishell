/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node_pipe_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:11:43 by sawang            #+#    #+#             */
/*   Updated: 2023/06/16 16:11:51 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

int	ast_node_pipe_create_and_insert(struct s_parser *parser)
{
	struct s_ast_node	*new_node;

	new_node = ft_calloc(1, sizeof(struct s_ast_node));
	if (new_node == NULL)
	{
		parser->malloc_fail = true;
		return (EXIT_FAILURE);
	}
	new_node->type = AST_NODE_PIPE;
	new_node->content = NULL;
	new_node->right = NULL;
	new_node->left = parser->head;
	parser->current = new_node;
	parser->head = parser->current;
	return (EXIT_SUCCESS);
}
