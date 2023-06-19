/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_maniputalor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 21:44:07 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 18:21:41 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/lexer.h"

void	scanner_init(struct s_scanner *scanner, char *line)
{
	scanner->start = line;
	scanner->current = line;
}

char	scanner_advance(struct s_scanner *scanner)
{
	scanner->current++;
	return (scanner->current[-1]);
}

void	scanner_recede(struct s_scanner *scanner)
{
	scanner->current--;
}

void	scanner_skipwhitespace(struct s_scanner *scanner)
{
	while (is_white_space(scanner_peek(*scanner)))
		scanner_advance(scanner);
}
