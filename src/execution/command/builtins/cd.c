/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/06/30 17:57:58 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "MINISHELL/execution/command/builtins.h"
#include "MINISHELL/error_printer.h"
#include "LIBFT/string.h"

#include <stdio.h>

//if no arguments after cd, use $HOME, which is in vars.environment,
// if no $HOME, use getcwd()
//if directory starts with '/', set curdir = directory. ||
// if directory starts with '.' or '..', set curdir = directory
// if curdir now doesnot start with '/',
// set curdir = $PWD - "PWD" + "/"(if no "/" at the end) + directory
// 1. clean the ./
// 2. 1).check error before if the previous component (before ..)
// is not a directory.
// 2). then clean the preceding_compoent/*../*following component
// 3.An implementation may further simplify curpath by
// removing any trailing <slash> characters that are not also
// leading <slash> characters,
	// replacing multiple non-leading consecutive <slash> characters
	// with a single <slash>,
	// and replacing three or more leading <slash> characters
	// with a single <slash>.
	// If, as a result of this canonicalization, the curpath variable is
	// null, no further steps shall be taken.
// Curpath shall be converted from an absolute pathname to
// an equivalent relative pathname if possible.
	//This conversion shall always be considered possible
	// if the value of PWD + "/"
	// is an initial substring of curpath.
// set chdir(curdir). if error, error message
// if success, set PWD = curdir before converted into relative path
// if no permission of directory or parent directory, do not update PWD

t_ms_exit_code	update_pwd(struct s_ms *ms);
t_ms_exit_code	buildin_cd_no_arg(struct s_ms *ms);

t_ms_exit_code	ms_execute_builtin_cd(struct s_ms *ms, t_sb_vector *command)
{
	t_ft_sb	*dir_sb;
	char	*dir;

	if (command->size == 1)
		return (buildin_cd_no_arg(ms));
	dir_sb = ft_vector_get(command, 1);
	dir = dir_sb->buffer;
	if (chdir(dir) == -1)
	{
		ms_error_printer_builtin("cd", dir, strerror(errno));
		return (EC_FAILURE);
	}
	return (update_pwd(ms));
}

t_ms_exit_code	update_pwd(struct s_ms *ms)
{
	char	buf[PATH_MAX + 4];

	if (!getcwd(buf + 4, PATH_MAX))
		return (EC_FAILURE);
	ft_memcpy(buf, "PWD=", 4);
	if (ms_vars_declare(&ms->vars, "PWD", buf))
		return (EC_FAILURE);
	return (EC_SUCCESS);
}

t_ms_exit_code	buildin_cd_no_arg(struct s_ms *ms)
{
	char	*home;

	home = (char *)ms_vars_database_get(&ms->vars.environment, "HOME");
	if (!home)
		return (EC_SUCCESS);
	if (chdir(home + 5) == -1)
	{
		ms_error_printer_builtin("cd", home, strerror(errno));
		return (EC_FAILURE);
	}
	return (update_pwd(ms));
}
