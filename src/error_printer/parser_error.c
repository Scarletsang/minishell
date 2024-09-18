/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 01:36:43 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 02:12:27 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "LIBFT/io.h"
#include "MINISHELL/lexer.h"
#include "MINISHELL/error_printer.h"

void	ms_error_printer_parser(struct s_token *token)
{
	if (token->type == TOKEN_EOF)
	{
		ms_error_printer_message("syntax error near unexpected token `EOF'");
		return ;
	}
	ft_putstr_fd(\
		"minishell: syntax error near unexpected token `", STDERR_FILENO);
	(void) !write(STDERR_FILENO, token->start, token->length);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	ms_error_printer_lexer(char *token_error_msg)
{
	ms_error_printer_message(token_error_msg);
	ms_error_printer_message("syntax error: unexpected end of file");
}
