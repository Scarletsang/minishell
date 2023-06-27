/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/06/27 22:57:29 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/execution/builtins.h"

//if no arguments after cd, use $HOME, which is in vars.environment, if no $HOME, use getcwd()
//if directory starts with '/', set curdir = directory. || if directory starts with '.' or '..', set curdir = directory
// if curdir now doesnot start with '/', set curdir = $PWD - "PWD" + "/"(if no "/" at the end) + directory
// 1. clean the ./
// 2. 1).check error before if the previous component (before ..) is not a directory.
// 2). then clean the preceding_compoent/*../*following component
// 3.An implementation may further simplify curpath by
// removing any trailing <slash> characters that are not also leading <slash> characters,
	// replacing multiple non-leading consecutive <slash> characters with a single <slash>,
	// and replacing three or more leading <slash> characters with a single <slash>.
	// If, as a result of this canonicalization, the curpath variable is null, no further steps shall be taken.
// Curpath shall be converted from an absolute pathname to an equivalent relative pathname if possible.
	//This conversion shall always be considered possible if the value of PWD + "/"
	// is an initial substring of curpath.
// set chdir(curdir). if error, error message
// if success, set PWD = curdir before converted into relative path
// if no permission of directory or parent directory, do not update PWD

t_ms_exit_code	ms_execute_builtin_cd(struct s_ms *ms, t_sb_vector *command)
{
	// (void) command;
	// (void) ms;
	t_ft_sb	*dir;
	char	dir_first;
	t_ft_sb	*curdir;

	if (command->size == 1)
		return (buildin_cd_no_arg(ms));
	dir = ft_vector_get(command, 1);
	dir_first = ft_sb_get(dir, 0);
	// dir_first = dir->buffer[0];
	if (dir_first == '.')
		curdir = dir;
	else if (dir_first == '/')
		curdir = dir;
	else
		curdir = get_curdir_from_pwd(ms->vars.environment, dir); //inside use ft_sb_perform to append, transfer PWD value into ft_sb
	update_curdir(&curdir);
	return (EXIT_SUCCESS);
}

//should I get pwd from PWD or getcwd()? if PWD, should use t_ft_sb, if not use char*
t_ft_sb	*get_curdir_from_pwd(t_ft_ht environment, t_ft_sb *dir)
{
	t_ft_sb	*curdir;
	t_ft_sb	*pwd;

}

int	update_curdir(t_ft_sb **curdir)
{

}

t_ms_exit_code	ms_cd_no_args(struct s_ms *ms)
{

}


