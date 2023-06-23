/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 01:16:59 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 02:07:18 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/io.h"
#include "MINISHELL/error_printer.h"

void	ms_error_printer_message(char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	ms_error_printer_command(char *cmd_name, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	ms_error_printer_builtin(char *cmd_name, char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	ms_error_printer_malloc_fails(void)
{
	ft_putstr_fd("minishell: internal error\n", STDERR_FILENO);
}
