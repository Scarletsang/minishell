/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:55:14 by htsang            #+#    #+#             */
/*   Updated: 2023/06/24 11:00:32 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "MINISHELL/execution/executor.h"
# include "MINISHELL/parser/content.h"
# include "MINISHELL/minishell.h"

///////////////////////////////////////////////////////////////////////////
////////////   private interface used by ms_executor_command   ////////////
///////////////////////////////////////////////////////////////////////////

t_ms_exit_code	ms_execute_builtin_echo(struct s_ms *ms, t_sb_vector *command);

t_ms_exit_code	ms_execute_builtin_cd(struct s_ms *ms, t_sb_vector *command);

t_ms_exit_code	ms_execute_builtin_pwd(struct s_ms *ms, t_sb_vector *command);

t_ms_exit_code	ms_execute_builtin_export(struct s_ms *ms, \
t_sb_vector *command);

t_ms_exit_code	ms_execute_builtin_unset(struct s_ms *ms, t_sb_vector *command);

t_ms_exit_code	ms_execute_builtin_env(struct s_ms *ms, t_sb_vector *command);

t_ms_exit_code	ms_execute_builtin_exit(struct s_ms *ms, t_sb_vector *command);

#endif