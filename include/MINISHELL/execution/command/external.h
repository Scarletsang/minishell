/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:55:52 by htsang            #+#    #+#             */
/*   Updated: 2023/06/28 11:46:06 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNAL_H
# define EXTERNAL_H

# include "MINISHELL/execution/executor.h"
# include "MINISHELL/parser/content.h"
# include "MINISHELL/minishell.h"

//////////////////////////////////////////////////
////////////   executable execution   ////////////
//////////////////////////////////////////////////

t_ms_exit_code	ms_execute_external_executable(struct s_ms *ms, \
t_sb_vector *command);

//////////////////////////////////////////////////////
////////////   execve builder interface   ////////////
//////////////////////////////////////////////////////

struct s_ms_execve_builder
{
	t_ft_sb		path;
	char		**argv;
};

t_ms_status		ms_execve_builder_init(struct s_ms_execve_builder *executable);

void			ms_execve_builder_free(struct s_ms_execve_builder *executable);

t_ms_status		ms_execve_builder_path_build(\
struct s_ms_execve_builder *executable, struct s_ms *ms, t_ft_sb *command_name);

bool			ms_execve_builder_path_is_executable(\
struct s_ms_execve_builder *executable);

t_ms_status		ms_execve_builder_argv_build(\
struct s_ms_execve_builder *executable, t_sb_vector *command);

#endif