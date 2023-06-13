/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:47:51 by sawang            #+#    #+#             */
/*   Updated: 2023/06/13 14:51:20 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

int	ast_node_str_set(struct s_parser *parser, t_sb *content_str)
{
	if (sb_init(content_str, 10) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (sb_perform(content_str, \
	sb_action_append_len(parser->current_token->token.start, \
	parser->current_token->token.length)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ast_node_cmd_create_and_link(struct s_parser *parser)
{
	struct s_ast_node	*new_node;

	new_node = malloc (sizeof(struct s_ast_node));
	if (new_node == NULL)
	{
		parser->malloc_fail = true;
		return (EXIT_FAILURE);
	}
	new_node->type = AST_NODE_CMD;
	new_node->content = NULL;
	new_node->right = NULL;
	new_node->left = NULL;
	if (parser->head == NULL)
		parser->head = new_node;
	else if (parser->head->type == AST_NODE_PIPE)
		parser->head->right = new_node;
	parser->current = new_node;
	return (EXIT_SUCCESS);
}

// struct s_ast_node	*ast_node_cmd_create(struct s_parser *parser)
// {
// 	struct s_ast_node	*new_node;

// 	new_node = malloc (sizeof(struct s_ast_node));
// 	if (new_node == NULL)
// 	{
// 		parser->malloc_fail = true;
// 		return (NULL);
// 	}
// 	new_node->type = AST_NODE_CMD;
// 	new_node->content = NULL;
// 	new_node->right = NULL;
// 	new_node->left = NULL;
// 	return (new_node);
// }

int	ast_node_pipe_create_and_link(struct s_parser *parser)
{
	struct s_ast_node	*new_node;

	new_node = malloc (sizeof(struct s_ast_node));
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
