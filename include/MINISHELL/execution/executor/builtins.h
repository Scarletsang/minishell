/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:55:14 by htsang            #+#    #+#             */
/*   Updated: 2023/06/15 21:29:26 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "MINISHELL/execution/executor.h"

t_executor_exit_code	ms_builtin_start(t_sb_vector *command, struct s_ms *ms);

t_executor_exit_code	ms_builtin_end(t_sb_vector *command, struct s_ms *ms);

///////////////////////////////////////////////////////////////////////////
////////////   private interface used by ms_executor_command   ////////////
///////////////////////////////////////////////////////////////////////////

int		ms_builtin_echo(t_sb_vector *command, struct s_ms *ms);

int		ms_builtin_cd(t_sb_vector *command, struct s_ms *ms);

int		ms_builtin_pwd(t_sb_vector *command, struct s_ms *ms);

int		ms_builtin_export(t_sb_vector *command, struct s_ms *ms);

int		ms_builtin_unset(t_sb_vector *command, struct s_ms *ms);

int		ms_builtin_env(t_sb_vector *command, struct s_ms *ms);

int		ms_builtin_exit(t_sb_vector *command, struct s_ms *ms);

#endif