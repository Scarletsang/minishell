/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:07:45 by sawang            #+#    #+#             */
/*   Updated: 2023/07/07 04:08:08 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/lexer.h"

struct s_token_list	*token_new(struct s_token token)
{
	struct s_token_list	*token_lst;

	token_lst = (struct s_token_list *)malloc(sizeof(struct s_token_list));
	if (!token_lst)
		return (NULL);
	token_lst->token = token;
	token_lst->next = NULL;
	return (token_lst);
}

void	token_add_back(struct s_lexer *lexer, struct s_token_list *token_lst)
{
	if (lexer->start == NULL)
	{
		lexer->start = token_lst;
		lexer->end = token_lst;
	}
	else
	{
		lexer->end->next = token_lst;
		lexer->end = lexer->end->next;
	}
}

void	lexer_free(struct s_lexer *lexer, \
t_token_cleaner del)
{
	struct s_token_list	*tmp_token_lst;

	if (!lexer->start || !del)
		return ;
	while (lexer->start)
	{
		tmp_token_lst = lexer->start;
		lexer->start = lexer->start->next;
		token_delone(tmp_token_lst, del);
	}
	lexer->end = NULL;
}

void	token_delone(struct s_token_list *token_lst, t_token_cleaner del)
{
	if (!token_lst || !del)
		return ;
	del(&token_lst->token);
	free(token_lst);
}

void	del(struct s_token *token_content)
{
	token_content->type = TOKEN_EOF;
	token_content->start = NULL;
	token_content->length = 0;
}
