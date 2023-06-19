/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assignword_updater.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:50:22 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 18:34:31 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/ctype.h"
#include "MINISHELL/lexer.h"

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

	if (!ft_isalpha(token.start[0]) && token.start[0] != '_')
		return (false);
	i = 0;
	while (i < token.length && token.start[i] != '=')
	{
		if (!ft_isalnum(token.start[i]) && token.start[i] != '_')
			return (false);
		i++;
	}
	if (i == token.length)
		return (false);
	return (true);
}
