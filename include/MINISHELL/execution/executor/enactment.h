/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enactment.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:05:38 by htsang            #+#    #+#             */
/*   Updated: 2023/06/19 15:49:25 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENACTMENT_H
# define ENACTMENT_H

# include "MINISHELL/minishell.h"
# include "MINISHELL/parser/ast.h"
# include "MINISHELL/execution/vars.h"
# include "MINISHELL/execution/executor.h"

/**
 * @brief structural execution
*/

t_executor_exit_code	ms_executor_enact(struct s_ms_executor *executor, \
struct s_ast_node *node, struct s_ms *ms);

t_executor_exit_code	ms_executor_enact_in_pipe(struct s_ms_executor *executor, \
struct s_ast_node *node, struct s_ms *ms);

t_executor_exit_code	ms_executor_enact_pipe(struct s_ms_executor *executor, \
struct s_ast_node *node, struct s_ms *ms);

t_executor_exit_code	ms_executor_enact_builtin(\
struct s_ms_executor *executor, struct s_ast_node_content *content, struct s_ms *ms);

t_executor_return_value	ms_executor_enact_command(\
struct s_ms_executor *executor, struct s_ast_node_content *content, struct s_ms *ms);

/**
 * @brief ast node execution (used by ms_executor_ast)
*/

t_executor_exit_code	ms_executor_expand_content(\
struct s_ast_node_content *content, struct s_ms *ms);

t_executor_exit_code	ms_executor_enact_assignment(\
struct s_ms_executor *executor, t_sb_vector *assignment, struct s_ms *ms);

t_executor_exit_code	ms_executor_enact_redirection_in(\
struct s_ms_executor *executor, t_ast_redirection_vector *redirection_in, \
struct s_ms *ms);

t_executor_exit_code	ms_executor_enact_redirection_out(\
struct s_ms_executor *executor, t_ast_redirection_vector *redirection_out, \
struct s_ms *ms);

t_executor_exit_code	ms_executor_enact_command_execution(\
struct s_ms_executor *executor, t_sb_vector *command, struct s_ms *ms);

#endif