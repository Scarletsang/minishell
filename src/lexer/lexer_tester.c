/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 21:58:30 by sawang            #+#    #+#             */
/*   Updated: 2023/05/30 23:01:12 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "MINISHELL/lexer/lexer.h"

void	token_lstitr_print(struct s_token_list *token_lst, void (*token_print)(void))
{
	struct s_token_list	*tmp_token_node;
	
	if (!token_lst || !token_print)
		return ;
	while (token_lst)
	{
		/* code */
	}

}

void	token_print(struct s_token)
{
	if
}

int	main(void)
{
	char			*line;
	struct s_lexer	lexer;
	int				err_code;

	line = readline("minishell>");
	lexer_init(&lexer);
	token_list_get(&lexer, line);
	token_lstitr_print(lexer.start, void (*token_print)(void));
	free(line); // Free the memory allocated by readline
	return (err_code);
}
