/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:20:44 by sawang            #+#    #+#             */
/*   Updated: 2023/06/17 17:47:36 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/ast.h"

struct s_ast_node	*ast_node_cmd_create(void)
{
	struct s_ast_node	*new_node;

	new_node = ft_calloc(1, sizeof(struct s_ast_node));
	if (new_node == NULL)
		return (NULL);
	new_node->type = AST_NODE_CMD;
	new_node->content = ft_calloc(1, sizeof(struct s_ast_node_content));
	if (new_node->content == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->right = NULL;
	new_node->left = NULL;
	if (ast_node_content_init(new_node->content) == EXIT_FAILURE)
		return (ast_node_free(new_node), NULL);
	return (new_node);
}

struct s_ast_node	*ast_node_pipe_create(void)
{
	struct s_ast_node	*new_node;

	new_node = ft_calloc(1, sizeof(struct s_ast_node));
	if (new_node == NULL)
		return (NULL);
	new_node->type = AST_NODE_PIPE;
	new_node->content = NULL;
	new_node->right = NULL;
	new_node->left = NULL;
	return (new_node);
}

void	ast_node_free(struct s_ast_node *node)
{
	if (node == NULL)
		return ;
	ast_node_free(node->left);
	ast_node_free(node->right);
	if (node->content)
	{
		ast_node_content_free(node->content);
		free(node);
	}
	else
		free(node);
}
