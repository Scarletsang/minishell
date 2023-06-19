/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scanner_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:56:54 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 18:22:15 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser.h"

void	parser_token_advance(struct s_parser *parser)
{
	parser->current_token = parser->current_token->next;
}

struct s_token_list	parser_token_peek_next(struct s_parser *parser)
{
	return (*parser->current_token->next);
}

struct s_token_list	parser_token_peek(struct s_parser *parser)
{
	return (*parser->current_token);
}
