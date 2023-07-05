/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:55:14 by htsang            #+#    #+#             */
/*   Updated: 2023/07/05 16:44:24 by sawang           ###   ########.fr       */
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

//builin utils for unset and export
bool			name_is_valid_indentifier(char *name, char delimeter);

#endif
