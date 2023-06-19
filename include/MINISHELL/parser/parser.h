/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 21:16:43 by htsang            #+#    #+#             */
/*   Updated: 2023/06/17 19:24:56 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "MINISHELL/parser/ast.h"
# include "MINISHELL/parser/content.h"

//if there is syntax error or malloc fail, free and exit right away
//PARSER_FAILURE means nothing to parse,
//PARSER_SUCCESS means there is something to parse
typedef enum e_parser_exit_code
{
	PARSER_SUCCESS,
	PARSER_FAILURE,
}			t_parser_exit_code;

struct s_parser
{
	struct s_ast_node	*head;
	struct s_ast_node	*current;
	struct s_token_list	*current_token;
	bool				malloc_fail;
};

void				parser_init(struct s_parser *parser, \
	struct s_token_list *start);
void				parser_free(struct s_parser *parser);

//parser main
bool				parser_check_before_run(struct s_lexer *lexer, \
	t_lexer_exit_code lexer_exit_code);
struct s_ast_node	*parser_run(char *line);
struct s_ast_node	*ast_parser_clear_when_failed(struct s_parser *parser, \
	char *err_message);
void				token_clear_when_parser_finished(struct s_lexer *lexer, \
t_token_cleaner del, char *err_message);

// TODO: interface for parser
t_parser_exit_code	parse_io_redirect(struct s_parser *parser);
t_parser_exit_code	parse_assignment_word(struct s_parser *parser);
t_parser_exit_code	parse_cmd_prefix(struct s_parser *parser);
t_parser_exit_code	parse_cmd_parameter(struct s_parser *parser);
t_parser_exit_code	parse_cmd_suffix(struct s_parser *parser);
t_parser_exit_code	parse_cmd_word(struct s_parser *parser);
t_parser_exit_code	parse_cmd(struct s_parser *parser);
t_parser_exit_code	parse_pipe(struct s_parser *parser);
t_parser_exit_code	parse_eof(struct s_parser *parser);
t_parser_exit_code	parse_complete_command(struct s_parser *parser);

// update ast
void				parser_ast_cmd_insert(struct s_parser *parser, \
	struct s_ast_node *new_node);
void				parser_ast_pipe_insert(struct s_parser *parser, \
	struct s_ast_node *new_node);

//parser token scanner utils
void				parser_token_advance(struct s_parser *parser);
struct s_token_list	parser_token_peek_next(struct s_parser *parser);
struct s_token_list	parser_token_peek(struct s_parser *parser);

//parser printer for testing

#endif
