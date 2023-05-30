/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:15:29 by sawang            #+#    #+#             */
/*   Updated: 2023/05/30 22:07:13 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <stdbool.h>

typedef enum e_err_code
{
	NO_LINE,
	ERROR_WHEN_LEX,
	MALLOC_FAIL
}			t_err_code;

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

// return all tokens which has the data structure of linked list

// lexer_init

// tokens_create (creating while reading the line)

#endif
