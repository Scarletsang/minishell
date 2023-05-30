/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:07:45 by sawang            #+#    #+#             */
/*   Updated: 2023/05/30 21:42:22 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/lexer/lexer.h"

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
	struct s_token_list	*token_last;

	if (!lexer->start)
		return ;
	token_last = (struct s_token_list *)ft_lstlast((t_list *)lexer->start);
	if (token_last)
	{
		token_last->next = token_lst;
		lexer->end = token_lst;
	}
	else
	{
		lexer->start = token_lst;
		lexer->end = token_lst;
	}
}

void	token_clear_when_lexer_failed(struct s_lexer *lexer, \
void (*del)(void *))
{
	struct s_token_lst	*tmp_token_lst;

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

void	token_delone(struct s_token_list *token_lst, void (*del)(void *))
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
