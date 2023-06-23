/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:21:44 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 21:23:46 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "MINISHELL/minishell.h"
# include "MINISHELL/parser/ast.h"
# include "MINISHELL/execution/executor.h"

enum	e_ms_execution_mode
{
	MODE_BUILTIN_ECHO,
	MODE_BUILTIN_CD,
	MODE_BUILTIN_PWD,
	MODE_BUILTIN_UNSET,
	MODE_BUILTIN_EXPORT,
	MODE_BUILTIN_ENV,
	MODE_BUILTIN_EXIT = 6,
	MODE_EXECUTABLE,
	MODE_NO_COMMAND
};

t_ms_exit_code	ms_execute_ast(struct s_ms *ms, \
struct s_ast_node *root);

/**
 * @brief structural execution
*/

t_ms_status		ms_execute_pipe(struct s_ms *ms, \
struct s_ast_node *pipe);

t_ms_exit_code	ms_execute_builtin(struct s_ms *ms, \
enum e_ms_execution_mode mode, struct s_ast_node_content *content);

t_ms_exit_code	ms_execute_command(struct s_ms *ms, \
struct s_ast_node_content *content);

/**
 * @brief ast node execution (used by ms_executor_ast)
*/

t_ms_status		ms_ast_node_content_expand(\
struct s_ast_node_content *content, struct s_ms *ms);

t_ms_status		ms_execute_assignment_and_redirection(struct s_ms *ms, \
struct s_ast_node_content *content);

t_ms_status		ms_execute_assignments(struct s_ms *ms, \
t_sb_vector *assignment);

t_ms_status		ms_execute_redirection_in(\
struct s_ms_executor *executor, t_ast_redirection_vector *redirection_in);

t_ms_status		ms_execute_redirection_out(\
t_ast_redirection_vector *redirection_out);

t_ms_exit_code	ms_execute_executable(struct s_ms *ms, \
t_sb_vector *command);

#endif