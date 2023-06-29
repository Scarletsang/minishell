/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:54:18 by htsang            #+#    #+#             */
/*   Updated: 2023/06/29 17:57:14 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_PRINTER_H
# define ERROR_PRINTER_H

# include "LIBFT/stringbuilder.h"
# include "MINISHELL/lexer.h"

void	ms_error_printer_message(const char *msg);

void	ms_error_printer_command(const char *cmd_name, const char *msg);

void	ms_error_printer_builtin(const char *cmd_name, const char *arg, \
const char *msg);

void	ms_error_printer_internal_error(void);

void	ms_error_printer_parser(struct s_token *token);

void	ms_error_printer_lexer(char *token_error_msg);

#endif