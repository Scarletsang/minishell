/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester_printer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:06:53 by sawang            #+#    #+#             */
/*   Updated: 2023/06/14 15:08:05 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

typedef enum e_printing_branch {
	LEFT,
	RIGHT
}			t_printing_branch;

struct s_ast_node	*from_identidier_to_tree(struct s_ast_node *node, \
t_printing_branch branch)
{
	if (branch == LEFT)
		return (node->left);
	else
		return (node->right);
}

struct s_ast_node	*from_identidier_to_tree(struct s_ast_node *node, t_printing_branch branch)
{
	if (branch == LEFT)
		return (node->left);
	else
		return (node->right);
}

void	print_ast_recursive(struct s_ast_node *node, int level, t_printing_branch branch)
{
	if (node == NULL)
		return ;

	// Print the right subtree
	print_tree_recursive(from_identidier_to_tree(node, branch), level + 1, branch);
	// Print the current node
	for (int i = 0; i < level; i++) {
		printf("    .");
    }
	printf("type: %d\t", node->type);
	print_ast_content(node->content);
	// Print the left subtree
	print_tree_recursive(from_identidier_to_tree(node, !branch), level + ((node->type != AST_NODE_CMD)), branch);
}

void	print_ast(struct s_ast_node *root)
{
    print_tree_recursive(root, 0, LEFT);
    printf("--------\n");
}
