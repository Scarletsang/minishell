/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:55:52 by htsang            #+#    #+#             */
/*   Updated: 2023/06/29 17:23:06 by htsang           ###   ########.fr       */
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
	t_ft_sb			command_path;
	t_ft_sb			*command_name;
	const char		*path_env;
	char			**argv;
};

t_ms_status		ms_execve_builder_init(struct s_ms_execve_builder *builder, \
struct s_ms *ms, t_sb_vector *command);

void			ms_execve_builder_free(struct s_ms_execve_builder *executable);

t_ms_exit_code	ms_execve_builder_path_build(\
struct s_ms_execve_builder *executable);

t_ms_status		ms_execve_builder_argv_build(\
struct s_ms_execve_builder *executable, t_sb_vector *command);

#endif