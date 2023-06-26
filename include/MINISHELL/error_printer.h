/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:54:18 by htsang            #+#    #+#             */
/*   Updated: 2023/06/25 04:42:05 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_PRINTER_H
# define ERROR_PRINTER_H

# include "LIBFT/stringbuilder.h"
# include "MINISHELL/lexer.h"

void	ms_error_printer_message(char *msg);

void	ms_error_printer_command(char *cmd_name, char *msg);

void	ms_error_printer_builtin(char *cmd_name, char *arg, char *msg);

void	ms_error_printer_internal_error(void);

void	ms_error_printer_parser(struct s_token *token);

void	ms_error_printer_lexer(char *token_error_msg);

#endif