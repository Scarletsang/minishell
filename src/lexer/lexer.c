/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:11:34 by sawang            #+#    #+#             */
/*   Updated: 2023/05/23 22:40:36 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/lexer/lexer.h"

void	lexer_init(struct s_lexer *lexer, char *line)
{
	lexer->start = NULL;
	lexer->end = NULL;
	lexer->scanner.start = line;
	lexer->scanner.current = line;
}

static bool	scanner_at_end(struct s_scanner scanner)
{
	return (*scanner.current == '\0');
}

// void	tokens_create(struct s_lexer *lexer)
// {
// 	char			c;
// 	struct s_token	token;

// 	while (1)
// 	{
// 		token = token_scan(lexer);
// 		if (token.type == TOKEN_EOF)
// 			break ;
// 		token_add_one(lexer, token);
// 	}
// };

// token	*idk(char *str)
// {
// 	if(match(lexer, ">>"))
// 		return (makeToken(str);
// 	if(match(lexer, ">"))
// 		return (makeToken(str);
// 	if ()
// 	return (NULL);
// }
static char	scanner_advance(struct s_scanner *scanner)
{
	scanner->current++;
	return (scanner->current[-1]);
}

struct s_token token_make(t_token_type type, struct s_scanner scanner, int length)
{
	struct s_token	token;

	token.type = type;
	token.start = scanner.start;
	token.length = length;
	return (token);
}

t_token_type	match(char expected, char previous, int *scanned)
{
	if (expected == '\0')
	{
		if (previous == '>')
			return (token_make(TOKEN_GREAT, lexer->scanner, 1));
		else if (previous == '<')
			return (token_make(TOKEN_LESS, lexer->scanner, 1));
	}
	if (expected == previous)
	{
		*scanned = 2;
		if (str[0] == '>')
			return (token_make(TOKEN_DGREAT, lexer->scanner, 2));
		else if (str[0] == '<')
			return (token_make(TOKEN_DLESS, lexer->scanner, 2));
	}
	else
	{
		*scanned = 1;
		if (str[0] == '>')
			return (token_make(TOKEN_GREAT, lexer->scanner, 1));
		else if (str[0] == '<')
			return (token_make(TOKEN_LESS, lexer->scanner, 1));
	}
	return (token_err("Unexpected character.\n"));
}

struct s_token	token_scan(struct s_lexer *lexer)
{
	char	c;
	int		scanned;

	scanned = 0;
	scanner_skipwhitespace(&lexer->scanner);
	lexer->scanner.start = lexer->scanner.current;
	if (scanner_at_end(lexer->scanner))
		return (token_make(TOKEN_EOF, lexer->scanner, 0));
	c = scanner_advance(&lexer->scanner);
	if (c == '|')
		return (token_make(TOKEN_PIPE, lexer->scanner, 1));
	// if (c == '\'')
	// 	return (token_make(TOKEN_QUOTE, lexer->scanner, 1));
	// if (c == '\"')
	// 	return (token_make(TOKEN_DQUOTE, lexer->scanner, 1));
	if (c == '>')
		return (match_operator(lexer->scanner, scanned));
	if (c == '<')
		return (token_make(match(lexer->scanner.current, c, &scanned), lexer->scanner, scanned));
	if (c == '\'' || c == '\"')
		return (match_word(lexer->scanner, &scanned));
	else
		return (match_word_or_assignmentword(lexer->scanner, &scanned));
	return (token_err("Unexpected character.\n"));
}

struct s_token_list	*token_list_get(char *line)
{
	struct s_lexer		lexer;
	struct s_token		token;

	if (!line)
		return (NULL);
	lexer_init(&lexer, line);
	while (1)
	{
		token = token_scan(&lexer);
		if (token.type == TOKEN_EOF)
			break ;
		token_add_one(lexer, token);
	}
	return (lexer.start);
}
