/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 21:58:30 by sawang            #+#    #+#             */
/*   Updated: 2023/05/31 19:05:06 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "MINISHELL/lexer/lexer.h"

char	*get_token_type(t_token_type token_type)
{
	char	*print;

	if (token_type == TOKEN_WORD)
		print = "WORD";
	else if (token_type == TOKEN_ASSIGNMENT_WORD)
		print = "ASSIGNMENT_WORD";
	else if (token_type == TOKEN_DLESS)
		print = "DLESS";
	else if (token_type == TOKEN_DGREAT)
		print = "DGREAT";
	else if (token_type == TOKEN_LESS)
		print = "LESS";
	else if (token_type == TOKEN_GREAT)
		print = "GREAT";
	else if (token_type == TOKEN_PIPE)
		print = "PIPE";
	else if (token_type == TOKEN_ERROR)
		print = "ERROR";
	else if (token_type == TOKEN_EOF)
		print = "EOF";
}

void	token_print(struct s_token token)
{
	printf("%15s'%.*s'\n", get_token_type(token.type), \
	token.length, token.start);
}

void	token_lstitr_print(struct s_token_list *token_lst, \
void (*token_print)(void))
{
	struct s_token_list	*tmp_token_node;

	if (!token_lst || !token_print)
		return ;
	tmp_token_node = token_lst;
	while (tmp_token_node)
	{
		token_print(tmp_token_node.token);
		tmp_token_node = tmp_token_node.next;
	}
}

int	main(void)
{
	char			*line;
	struct s_lexer	lexer;
	int				err_code;

	line = readline("minishell>");
	lexer_init(&lexer);
	token_list_get(&lexer, line);
	token_lstitr_print(lexer.start, token_print);
	free(line); // Free the memory allocated by readline
	return (err_code);
}
