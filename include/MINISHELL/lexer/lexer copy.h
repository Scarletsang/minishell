/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer copy.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:15:29 by sawang            #+#    #+#             */
/*   Updated: 2023/05/22 15:48:49 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <stdbool.h>
# include "MINISHELL/vector.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_ASSIGNMENT_WORD,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_DLESS,
	TOKEN_DGREAT,
	TOKEN_LESS,
	TOKEN_GREAT,
	TOKEN_PIPE,
	TOKEN_ERROR,
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

typedef t_vector t_tokens;

struct s_lexer
{
	t_tokens			tokens;
	struct s_scanner	scanner;
};

#endif
