/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/06/22 22:22:38 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/execution/executor/builtins.h"

//if no arguments after cd, use $HOME, which is in vars.environment, if no $HOME, use getcwd()
//if directory starts with '/', set curdir = directory. || if directory starts with '.' or '..', set curdir = directory
// if curdir now doesnot start with '/', set curdir = $PWD - "PWD" + "/"(if no "/" at the end) + directory
// 1. clean the ./
// 2. clean the preceding_compoent/*../*following component
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
int		ms_builtin_cd(struct s_ms_executor *executor, t_sb_vector *command, \
struct s_ms *ms)
{
	(void) executor;
	(void) command;
	(void) ms;
	return (EXIT_SUCCESS);
}
