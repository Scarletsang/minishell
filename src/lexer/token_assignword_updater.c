/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assignword_updater.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:50:22 by sawang            #+#    #+#             */
/*   Updated: 2023/06/01 14:52:50 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/lexer/lexer.h"

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
		if (tmp_token_node->token.type == TOKEN_WORD)
		{
			if (token_is_assignmentword(tmp_token_node->token))
				token_update(&tmp_token_node->token);
		}
		tmp_token_node = tmp_token_node->next;
	}
}

bool	token_is_assignmentword(struct s_token token)
{
	int	i;
	int	j;

	if (token.start[0] == '=' || ft_isdigit(token.start[0]))
		return (false);
	i = 0;
	while (i < token.length && token.start[i] != '=')
		i++;
	j = 0;
	while (token.start[i] && j < i)
	{
		if (!((ft_isalnum(token.start[j])) || token.start[j] == '_'))
			return (false);
		j++;
	}
	return (true);
}
