/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:26:46 by htsang            #+#    #+#             */
/*   Updated: 2023/06/28 11:45:53 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "MINISHELL/execution.h"

///////////////////////////////////////////////
////////////   command execution   ////////////
///////////////////////////////////////////////

/**
 * @brief This module provides two kinds of command execution:
 * 1. a external executable execution, which will actually call an external
 * executable file
 * 2. a builtin execution, which will call a builtin function
*/

/**
 * @brief command execution has three steps:
 * 1. expand ast node content
 * 2. assignments
 * 3. redirections
 * 4. execute command
*/
t_ms_exit_code	ms_execute_external(struct s_ms *ms, \
struct s_ast_node_content *content);

/**
 * @brief builtin execution has three steps:
 * 1. expand ast node content
 * 2. declares (assignments but not added to envp directly, but to the shell 
 * database in vars)
 * 3. redirections
 * 4. execute builtin
*/
t_ms_exit_code	ms_execute_builtin(struct s_ms *ms, \
enum e_ms_execution_mode mode, struct s_ast_node_content *content);

/**
 * @brief Step 1 of a command execution: expand the content of an ast node
*/
t_ms_status		ms_ast_node_content_expand(\
struct s_ast_node_content *content, struct s_ms *ms);

/**
 * @brief Step 2 of a command execution: declare/asisgn variables.
 * - Declares are assignments but not added to envp directly, but to the shell
 * database in vars.
 * - Assignments are added to envp directly.
*/

t_ms_status		ms_execute_declares(struct s_ms *ms, \
t_sb_vector *assignments);

t_ms_status		ms_execute_assignments(struct s_ms *ms, \
t_sb_vector *assignment);

/**
 * @brief Step 3 of a command execution: redirections.
*/

t_ms_status		ms_execute_redirection_in(\
struct s_ms_executor *executor, t_ast_redirection_vector *redirection_in);

t_ms_status		ms_execute_redirection_out(\
struct s_ms_executor *executor, t_ast_redirection_vector *redirection_out);

/**
 * @brief Step 2 and 3 of a command execution when no command is present:
 * declarations and redirections.
 * For example: 'a=3' is a command which only declares the variable 'a'
 * and assign it the value 3.
*/
t_ms_status		ms_execute_declares_and_redirections(\
struct s_ms *ms, struct s_ast_node_content *content);

/**
 * @brief Step 2 and 3 of a command execution when a command is present:
 * assignments and redirections.
 * For example: 'a=3 bash' is a command which stores "a=3" in the envp that
 * will be passed to the immediate followed executable, in this example, the
 * executable is 'bash'.
*/
t_ms_status		ms_execute_assignments_and_redirections(\
struct s_ms *ms, struct s_ast_node_content *content);

#endif
