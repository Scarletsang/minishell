/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:11:34 by sawang            #+#    #+#             */
/*   Updated: 2023/05/30 22:50:30 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/lexer/lexer.h"

void	lexer_init(struct s_lexer *lexer)
{
	lexer->start = NULL;
	lexer->end = NULL;
	// lexer->scanner.start = line;
	// lexer->scanner.current = line;
}

t_err_code			token_list_get(struct s_lexer *lexer, char *line)
{
	// struct s_lexer		lexer;
	struct s_scanner	scanner;
	struct s_token		token;
	struct s_token_list	*token_lst;

	if (!line)
		return (NO_LINE);
	// lexer_init(&lexer, line);
	scanner_init(&scanner, line);
	while (1)
	{
		token = token_scan(&scanner);
		if (token.type == TOKEN_ERROR)
			return (token_clear_when_lexer_failed(lexer), ERROR_WHEN_LEX);
		if (token.type == TOKEN_EOF)
			break ;
		token_lst = token_new(token);
		if (!token_lst)
			return (token_clear_when_lexer_failed(lexer), MALLOC_FAIL);
		token_add_back(lexer, token_lst);
	}
	return (lexer);
}
