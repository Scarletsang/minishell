/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:48:21 by htsang            #+#    #+#             */
/*   Updated: 2023/06/05 19:10:03 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "MINISHELL/vector.h"
# include "MINISHELL/stringbuilder.h"
# include "MINISHELL/parser/redirection.h"

typedef t_vector t_sb_vector;

struct s_AST_node_content
{
	t_AST_redirection_vector	redirection_in;
	t_AST_redirection_vector	redirection_out;
	t_sb_vector					assignment;
	t_sb_vector					command;
};

enum e_AST_node_type
{
	AST_NODE_COMMAND,
	AST_NODE_PIPE,
	AST_NODE_AND,
	AST_NODE_OR
};

struct s_AST_node
{
	enum e_AST_node_type		type;
	struct s_AST_node_content	*content;
	struct s_AST_node			*left;
	struct s_AST_node			*right;
};

#endif