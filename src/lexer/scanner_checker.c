/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 22:03:01 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 18:21:35 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/lexer.h"

bool	is_white_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f');
}

bool	scanner_at_end(struct s_scanner scanner)
{
	return (*scanner.current == '\0');
}

char	scanner_peek(struct s_scanner scanner)
{
	return (*scanner.current);
}

bool	scanner_is_at_delimeter(struct s_scanner scanner)
{
	return (is_white_space(scanner_peek(scanner)) || \
	scanner_peek(scanner) == '\0' || \
	scanner_peek(scanner) == '>' || scanner_peek(scanner) == '<' || \
	scanner_peek(scanner) == '|');
}
