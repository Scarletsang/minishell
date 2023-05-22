/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:11:34 by sawang            #+#    #+#             */
/*   Updated: 2023/05/22 15:04:43 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/lexer/lexer.h"

void	lexer_init(struct s_lexer *lexer, char *line)
{
	lexer->token_list = NULL;
	lexer->scanner.start = line;
	lexer->scanner.current = line;
}

static bool	scanner_at_end(struct s_scanner scanner)
{
	return (scanner.current == '\0');
}

void	tokens_create(struct s_lexer *lexer)
{
	while (scanner_at_end(lexer->scanner) == false)
	{
		/* code */
	}

};

struct s_token_list	*token_list_get(char *line)
{
	struct s_lexer		lexer;

	if (!line)
		return (NULL);
	lexer_init(&lexer, line);
	tokens_create(&lexer);
	return (lexer.token_list);
}
