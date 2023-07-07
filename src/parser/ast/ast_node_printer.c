/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_printer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:06:53 by sawang            #+#    #+#             */
/*   Updated: 2023/07/07 11:08:04 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "MINISHELL/parser/ast.h"

static struct s_ast_node	*from_identidier_to_tree(struct s_ast_node *node, \
bool is_left)
{
	if (is_left)
		return (node->left);
	else
		return (node->right);
}

static void	ast_recursive_print(struct s_ast_node *node, \
int level, bool is_left)
{
	int	i;

	if (node == NULL)
		return ;
	i = 0;
	ast_recursive_print(\
		from_identidier_to_tree(node, is_left), level + 1, is_left);
	while (i < level)
	{
		printf("    .");
		i++;
	}
	printf("type: %d\t", node->type);
	ast_node_content_print(node->content);
	printf("\n");
	ast_recursive_print(\
		from_identidier_to_tree(node, !is_left), \
		level + ((node->type != AST_NODE_CMD)), is_left);
}

void	ast_print(struct s_ast_node *root)
{
	printf("--------------------------------------------------\n");
	ast_recursive_print(root, 0, true);
	printf("--------------------------------------------------\n");
}
