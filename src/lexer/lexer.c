/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:11:34 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 18:33:51 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "MINISHELL/lexer.h"

void	lexer_init(struct s_lexer *lexer)
{
	lexer->start = NULL;
	lexer->end = NULL;
}

t_lexer_exit_code	token_list_get(struct s_lexer *lexer, char *line)
{
	struct s_scanner	scanner;
	struct s_token		token;
	struct s_token_list	*token_lst;

	if (*line == '\0')
		return (NO_LINE);
	scanner_init(&scanner, line);
	while (1)
	{
		token = token_scan(&scanner);
		token_lst = token_new(token);
		if (!token_lst)
			return (token_clear_when_lexer_failed(lexer, \
			(t_token_cleaner)del, "malloc failed"), MALLOC_FAIL);
		token_add_back(lexer, token_lst);
		if (token.type == TOKEN_ERROR)
			return (printf("%s\n", token.start), ERROR_WHEN_LEX);
		if (token.type == TOKEN_EOF)
			break ;
	}
	token_lstitr_update_assignmentword(lexer->start, \
		(t_token_updater)token_update);
	return (LEXER_SUCCESS);
}
