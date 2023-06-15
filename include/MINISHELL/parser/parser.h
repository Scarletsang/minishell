/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 21:16:43 by htsang            #+#    #+#             */
/*   Updated: 2023/06/15 20:51:11 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "MINISHELL/parser/ast.h"

struct s_parser
{
	struct s_ast_node	*head;
	struct s_ast_node	*current;
	struct s_token_list	*current_token;
};

// TODO: interface for parser

#endif