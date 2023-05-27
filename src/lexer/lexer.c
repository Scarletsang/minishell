/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:11:34 by sawang            #+#    #+#             */
/*   Updated: 2023/05/27 19:51:44 by sawang           ###   ########.fr       */
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

static bool	is_white_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f');
}

static bool	scanner_at_end(struct s_scanner scanner)
{
	return (*scanner.current == '\0');
}

static char	scanner_peek(struct s_scanner scanner)
{
	return (*scanner.current);
}

static char	scanner_peak_next(struct s_scanner scanner)
{
	if (scanner_at_end(scanner))
		return ('\0');
	return (scanner.current[1]);
}

static bool	scanner_is_at_delimeter(struct s_scanner scanner)
{
	return (is_white_space(scanner_peek(scanner)) || \
	scanner_peek(scanner) == '\0' || \
	scanner_peek(scanner) == '>' || scanner_peek(scanner) == '<');
}

static char	scanner_advance(struct s_scanner *scanner)
{
	scanner->current++;
	return (scanner->current[-1]);
}

static void	scanner_recede(struct s_scanner *scanner)
{
	scanner->current--;
}

static void	scanner_skipwhitespace(struct s_scanner *scanner)
{
	int		i;

	while (is_white_space(scanner_peek(*scanner)))
		scanner_advance(scanner);

}

struct s_token	token_make(t_token_type type, struct s_scanner scanner)
{
	struct s_token	token;

	token.type = type;
	token.start = scanner.start;
	token.length = scanner.current - scanner.start;
	return (token);
}

struct s_token	token_error(const char *message)
{
	struct s_token	token;

	token.type = TOKEN_ERROR;
	token.start = message;
	token.length = ft_strlen(message);
	return (token);
}

struct s_token	token_match_operator(struct s_scanner *scanner, char c)
{
	if (c == '>')
	{
		if (*scanner->current == '>')
		{
			scanner_advance(scanner);
			return (token_make(TOKEN_DGREAT, *scanner));
		}
		else
			return (token_make(TOKEN_GREAT, *scanner));
	}
	if (c == '<')
	{
		if (*scanner->current == '<')
		{
			scanner_advance(scanner);
			return (token_make(TOKEN_DLESS, *scanner));
		}
		else
			return (token_make(TOKEN_LESS, *scanner));
	}
	return (token_error("Unexpected character.\n"));
}

//token word
struct s_token	token_match_word(struct s_scanner *scanner)
{
	char	c;

	while (1)
	{
		if (scanner_peek(*scanner) == '\"' || scanner_peek(*scanner) == '\'')
		{
			c = scanner_peek(*scanner);
			scanner_advance(scanner);
			while (scanner_peek(*scanner) != c && !scanner_at_end(*scanner))
				scanner_advance(scanner);
			if (scanner_at_end(*scanner))
				return (token_error("Unterminated string.\n"));
			scanner_advance(scanner);
			if (is_token_delimeter(scanner_peek(*scanner)))
				return (token_make(TOKEN_WORD, *scanner));
		}
		else
		{
			scanner_advance(scanner);
			if (is_token_delimeter(scanner_peek(*scanner)))
				return (token_make(TOKEN_WORD, *scanner));
		}
	}
}

struct s_token	token_scan(struct s_lexer *lexer)
{
	char	c;

	scanner_skipwhitespace(&lexer->scanner);
	lexer->scanner.start = lexer->scanner.current;
	if (scanner_at_end(lexer->scanner))
		return (token_make(TOKEN_EOF, lexer->scanner));
	c = scanner_advance(&lexer->scanner);
	if (c == '|')
		return (token_make(TOKEN_PIPE, lexer->scanner));
	if (c == '>' || c == '<')
		return (token_match_operator(&lexer->scanner, c));
	// if (c == '<')
	// 	return (match_operator(lexer->scanner, c));
	// if (c == '\'' || c == '\"')
	// 	return (token_match_word(&lexer->scanner, c));
	else
	{
		scanner_recede(&lexer->scanner);
		return (token_match_word(&lexer->scanner));
	}
	return (token_error("Unexpected character.\n"));
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
