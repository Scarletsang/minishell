/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 04:37:35 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/execution/command/builtins.h"
#include <limits.h>
#include "LIBFT/string.h"
#include "LIBFT/io.h"
#include "MINISHELL/error_printer.h"

//should builtin pwd use getcwd() or environment variable PWD?
// how large should the size be?
t_ms_exit_code	ms_execute_builtin_pwd(struct s_ms *ms, t_sb_vector *command)
{
	char	buf[PATH_MAX];

	(void)ms;
	(void)command;
	if (!getcwd(buf, PATH_MAX))
	{
		ms_error_printer_builtin("pwd", NULL, strerror(errno));
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(buf, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
