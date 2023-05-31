/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:11:34 by sawang            #+#    #+#             */
/*   Updated: 2023/05/31 22:23:34 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/lexer/lexer.h"
#include <stdio.h>

void	lexer_init(struct s_lexer *lexer)
{
	lexer->start = NULL;
	lexer->end = NULL;
	// lexer->scanner.start = line;
	// lexer->scanner.current = line;
}

t_err_code	token_list_get(struct s_lexer *lexer, char *line)
{
	struct s_scanner	scanner;
	struct s_token		token;
	struct s_token_list	*token_lst;

	if (!line)
		return (NO_LINE);
	scanner_init(&scanner, line);
	while (1)
	{
		token = token_scan(&scanner);
		if (token.type == TOKEN_ERROR)
			return (token_clear_when_lexer_failed(lexer, \
			(t_token_cleaner)del, token.start), ERROR_WHEN_LEX);
		if (token.type == TOKEN_EOF)
			break ;
		token_lst = token_new(token);
		if (!token_lst)
			return (token_clear_when_lexer_failed(lexer, \
			(t_token_cleaner)del, "malloc failed"), MALLOC_FAIL);
		token_add_back(lexer, token_lst);
	}
	token_lstitr_update_assignmentword(lexer->start, \
		(t_token_updater)token_update);
	return (LEXER_SUCCESS);
}

void	token_update(struct s_token *token)
{
	token->type = TOKEN_ASSIGNMENT_WORD;
}

void	token_lstitr_update_assignmentword(struct s_token_list *token_lst, \
t_token_updater token_update)
{
	struct s_token_list	*tmp_token_node;

	if (!token_lst || !token_update)
		return ;
	tmp_token_node = token_lst;
	while (tmp_token_node)
	{
		if (token_is_assignmentword(tmp_token_node->token))
			token_update(&tmp_token_node->token);
		tmp_token_node = tmp_token_node->next;
	}
}

bool	token_is_assignmentword(struct s_token token)
{
	char	*token_str;

	token_str = ft_substr(token.start, 0, token.length);

	free(token_str);
}
