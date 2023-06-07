/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:48:21 by htsang            #+#    #+#             */
/*   Updated: 2023/06/07 12:37:27 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "MINISHELL/vector.h"
# include "MINISHELL/stringbuilder.h"
# include "MINISHELL/parser/redirection.h"

typedef t_vector	t_sb_vector;

struct s_ast_node_content
{
	t_ast_redirection_vector	redirection_in;
	t_ast_redirection_vector	redirection_out;
	t_sb_vector					assignment;
	t_sb_vector					command;
};

// TODO: interface for AST node content

enum e_ast_node_type
{
	AST_NODE_COMMAND,
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

#endif
