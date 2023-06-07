/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scanner_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:56:54 by sawang            #+#    #+#             */
/*   Updated: 2023/06/07 18:46:09 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

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
