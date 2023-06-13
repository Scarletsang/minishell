/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 21:16:43 by htsang            #+#    #+#             */
/*   Updated: 2023/06/13 15:28:37 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "MINISHELL/parser/ast.h"
# include "MINISHELL/lexer/lexer.h"

//if there is syntax error or malloc fail, free and exit right away
//PARSER_FAILURE means nothing to parse,
//PARSER_SUCCESS means there is something to parse
typedef enum e_parser_exit_code
{
	PARSER_SUCCESS,
	PARSER_FAILURE,
	// MALLOC_FAIL
}			t_parser_exit_code;

struct s_parser
{
	struct s_ast_node	*head;
	struct s_ast_node	*current;
	struct s_token_list	*current_token;
	// struct s_token_list *start_token;
	bool				malloc_fail;
};

// TODO: interface for parser



//parser token scanner utils
void				parser_token_advance(struct s_parser *parser);
struct s_token_list	parser_token_peek_next(struct s_parser *parser);
struct s_token_list	parser_token_peek(struct s_parser *parser);
#endif
