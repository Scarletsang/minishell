/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester_printer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:06:53 by sawang            #+#    #+#             */
/*   Updated: 2023/06/26 15:50:14 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_tester.h"

typedef enum e_printing_branch {
	LEFT,
	RIGHT
}			t_printing_branch;

static struct s_ast_node	*from_identidier_to_tree(struct s_ast_node *node, \
t_printing_branch branch)
{
	if (branch == LEFT)
		return (node->left);
	else
		return (node->right);
}

static void	print_ast_recursive(struct s_ast_node *node, int level, t_printing_branch branch)
{
	if (node == NULL)
		return ;

	int i = 0;
	// Print the right subtree
	print_ast_recursive(from_identidier_to_tree(node, branch), level + 1, branch);
	// Print the current node
	while (i < level)
	{
		printf("    .");
		i++;
	}
	printf("type: %d\t", node->type);
	print_ast_content(node->content);
	printf("\n");
	// Print the left subtree
	print_ast_recursive(from_identidier_to_tree(node, !branch), level + ((node->type != AST_NODE_CMD)), branch);
}

void	print_ast(struct s_ast_node *root)
{
    printf("--------------------------------------------------\n");
    print_ast_recursive(root, 0, LEFT);
    printf("--------------------------------------------------\n");
}
