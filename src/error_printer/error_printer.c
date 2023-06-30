/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 01:16:59 by htsang            #+#    #+#             */
/*   Updated: 2023/06/29 17:57:43 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/io.h"
#include "MINISHELL/error_printer.h"

void	ms_error_printer_message(const char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd((char *) msg, STDERR_FILENO);
}

void	ms_error_printer_command(const char *cmd_name, const char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *) cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd((char *) msg, STDERR_FILENO);
}

void	ms_error_printer_builtin(const char *cmd_name, const char *arg, \
const char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *) cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd((char *) arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd((char *) msg, STDERR_FILENO);
}

void	ms_error_printer_internal_error(void)
{
	ft_putstr_fd("minishell: internal error\n", STDERR_FILENO);
}
