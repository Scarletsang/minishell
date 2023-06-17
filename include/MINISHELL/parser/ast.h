/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:48:21 by htsang            #+#    #+#             */
/*   Updated: 2023/06/17 18:24:29 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "MINISHELL/parser/content.h"

enum e_ast_node_type
{
	AST_NODE_CMD,
	AST_NODE_PIPE,
	AST_NODE_AND,
	AST_NODE_OR
};

struct s_ast_node
{
	enum e_ast_node_type		type;
	struct s_ast_node_content	*content;
	struct s_ast_node			*left;
	struct s_ast_node			*right;
};

// TODO: interface for AST node
// should takee no param,
// malloc failure can be checked outside and set malloc fail outside
struct s_ast_node	*ast_node_cmd_create(void);
struct s_ast_node	*ast_node_pipe_create(void);

void				ast_node_free(struct s_ast_node *node);

#endif
