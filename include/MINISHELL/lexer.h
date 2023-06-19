/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:15:29 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 15:27:38 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>

typedef enum e_lexer_exit_code
{
	LEXER_SUCCESS,
	ERROR_WHEN_LEX,
	NO_LINE,
	MALLOC_FAIL
}			t_lexer_exit_code;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_ASSIGNMENT_WORD,
	TOKEN_DLESS,
	TOKEN_DGREAT,
	TOKEN_LESS,
	TOKEN_GREAT,
	TOKEN_PIPE,
	TOKEN_ERROR,
	TOKEN_EOF
}				t_token_type;

struct s_scanner
{
	char	*start;
	char	*current;
}		t_scanner;

struct s_token
{
	t_token_type	type;
	char			*start;
	int				length;
};

struct s_token_list
{
	struct s_token		token;
	struct s_token_list	*next;
};

struct s_lexer
{
	struct s_token_list	*start;
	struct s_token_list	*end;
	// struct s_scanner	scanner;
};

typedef void	(*t_token_cleaner)(void *);
typedef void	(*t_token_updater)(void *);
typedef void	(*t_token_printer)(void *);
/**
lexer
*/
void				lexer_init(struct s_lexer *lexer);
t_lexer_exit_code	token_list_get(struct s_lexer *lexer, char *line);

/**
scanner
*/
//with updating scanner info
void				scanner_init(struct s_scanner *scanner, char *line);
char				scanner_advance(struct s_scanner *scanner);
void				scanner_recede(struct s_scanner *scanner);
void				scanner_skipwhitespace(struct s_scanner *scanner);
//with only checking scanner info
bool				is_white_space(char c);
bool				scanner_at_end(struct s_scanner scanner);
char				scanner_peek(struct s_scanner scanner);
bool				scanner_is_at_delimeter(struct s_scanner scanner);

/**tokenizer
*/
//matching and making the token by scanning through the string
struct s_token		token_make(t_token_type type, struct s_scanner scanner);
struct s_token		token_error(const char *message);
struct s_token		token_match_operator(struct s_scanner *scanner, char c);
struct s_token		token_match_word(struct s_scanner *scanner);
struct s_token		token_scan(struct s_scanner *scanner);
//adding tokens to a linked list, clear when sth failed
struct s_token_list	*token_new(struct s_token token);
void				token_add_back(struct s_lexer *lexer, \
				struct s_token_list *token_lst);
void				token_clear_when_lexer_failed(struct s_lexer *lexer, \
t_token_cleaner del, char *err_message);
void				token_delone(struct s_token_list *token_lst, \
				t_token_cleaner del);
void				del(struct s_token *token_content);
//update token if it should be ASSIGNMENT_WORD
void				token_update(struct s_token *token);
void				token_lstitr_update_assignmentword(\
				struct s_token_list *token_lst, t_token_updater token_update);
bool				token_is_assignmentword(struct s_token token);
/**lexer tester
*/


#endif
