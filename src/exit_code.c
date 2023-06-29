/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:05:48 by htsang            #+#    #+#             */
/*   Updated: 2023/06/29 17:25:35 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "MINISHELL/status_code.h"
#include "MINISHELL/error_printer.h"

t_ms_exit_code	ms_exit_code_determine(char *command_name, \
bool is_path)
{
	struct stat		path_stat;
	t_ms_exit_code	exit_code;

	exit_code = EC_SUCCESS;
	if (access(command_name, F_OK) == -1)
	{
		if (is_path)
			exit_code = __EC_NO_SUCH_FILE;
		else
			exit_code = EC_COMMAND_NOT_FOUND;
	}
	else if (stat(command_name, &path_stat) == -1)
	{
		exit_code = __EC_INTERNAL_ERROR;
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		exit_code = __EC_IS_A_DIR;
	}
	else if (access(command_name, X_OK) == -1)
	{
		exit_code = EC_COMMAND_NO_PERMISSION;
	}
	return (exit_code);
}

t_ms_exit_code	ms_exit_code_print(t_ms_exit_code exit_code, \
char *command_name)
{
	if (exit_code == EC_COMMAND_NOT_FOUND)
	{
		ms_error_printer_command(command_name, "command not found");
	}
	else if (exit_code == EC_COMMAND_NO_PERMISSION)
	{
		ms_error_printer_command(command_name, strerror(EACCES));
	}
	else if (exit_code == __EC_NO_SUCH_FILE)
	{
		ms_error_printer_command(command_name, strerror(ENOENT));
	}
	else if (exit_code == __EC_IS_A_DIR)
	{
		ms_error_printer_command(command_name, strerror(EISDIR));
	}
	else if (exit_code == __EC_INTERNAL_ERROR)
	{
		ms_error_printer_internal_error();
	}
	return (exit_code);
}

t_ms_exit_code	ms_exit_code_output(t_ms_exit_code exit_code)
{
	if (exit_code == __EC_NO_SUCH_FILE)
	{
		exit_code = EC_COMMAND_NOT_FOUND;
	}
	else if (exit_code == __EC_IS_A_DIR)
	{
		exit_code = EC_COMMAND_NO_PERMISSION;
	}
	else if (exit_code == __EC_INTERNAL_ERROR)
	{
		exit_code = EC_FAILURE;
	}
	return (exit_code);
}

t_ms_exit_code	ms_exit_code_evaluate(char *command_name, \
bool is_path, bool print)
{
	t_ms_exit_code	exit_code;

	exit_code = ms_exit_code_determine(command_name, is_path);
	if (print)
		ms_exit_code_print(exit_code, command_name);
	return (ms_exit_code_output(exit_code));
}
