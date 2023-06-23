/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:55:14 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 17:51:25 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "MINISHELL/execution/executor.h"
# include "MINISHELL/parser/content.h"
# include "MINISHELL/minishell.h"

t_executor_exit_code	ms_builtin_start(struct s_ms *ms, \
t_sb_vector *command);

t_executor_exit_code	ms_builtin_end(struct s_ms *ms, t_sb_vector *command);

///////////////////////////////////////////////////////////////////////////
////////////   private interface used by ms_executor_command   ////////////
///////////////////////////////////////////////////////////////////////////

int		ms_execute_builtin_echo(struct s_ms *ms, t_sb_vector *command);

int		ms_execute_builtin_cd(struct s_ms *ms, t_sb_vector *command);

int		ms_execute_builtin_pwd(struct s_ms *ms, t_sb_vector *command);

int		ms_execute_builtin_export(struct s_ms *ms, t_sb_vector *command);

int		ms_execute_builtin_unset(struct s_ms *ms, t_sb_vector *command);

int		ms_execute_builtin_env(struct s_ms *ms, t_sb_vector *command);

int		ms_execute_builtin_exit(struct s_ms *ms, t_sb_vector *command);

#endif