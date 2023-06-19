/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 22:04:53 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 18:34:08 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/string.h"
#include "MINISHELL/lexer.h"

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
	token.start = (char *)message;
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
	return (token_error("Unexpected character."));
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
				return (token_error("Unterminated string when matching quote"));
			scanner_advance(scanner);
			if (scanner_is_at_delimeter(*scanner))
				return (token_make(TOKEN_WORD, *scanner));
		}
		else
		{
			scanner_advance(scanner);
			if (scanner_is_at_delimeter(*scanner))
				return (token_make(TOKEN_WORD, *scanner));
		}
	}
}

struct s_token	token_scan(struct s_scanner *scanner)
{
	char	c;

	scanner_skipwhitespace(scanner);
	scanner->start = scanner->current;
	if (scanner_at_end(*scanner))
		return (token_make(TOKEN_EOF, *scanner));
	c = scanner_advance(scanner);
	if (c == '|')
		return (token_make(TOKEN_PIPE, *scanner));
	if (c == '>' || c == '<')
		return (token_match_operator(scanner, c));
	else
	{
		scanner_recede(scanner);
		return (token_match_word(scanner));
	}
	return (token_error("Unexpected character."));
}
