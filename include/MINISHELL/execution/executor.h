/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:18:03 by htsang            #+#    #+#             */
/*   Updated: 2023/06/11 17:28:15 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdlib.h>
# include <unistd.h>
# include "MINISHELL/minishell.h"
# include "MINISHELL/parser/ast.h"
# include "MINISHELL/execution/expander.h"
# include "MINISHELL/execution/executor/piper.h"

typedef enum s_executor_exit_code
{
	EXECUTION_SUCCESS,
	EXECUTION_FAILURE,
	EXECUTION_ERROR
}				t_executor_exit_code;

typedef int	t_executor_return_value;

////////////////////////////////////////////////
////////////   executor interface   ////////////
////////////////////////////////////////////////

struct s_ms_executor
{
	struct s_ms_piper	piper;
	pid_t				last_child_pid;
};

void					ms_executor_init(struct s_ms_executor *executor);

t_executor_return_value	ms_executor_wait(struct s_ms_executor *executor);

t_executor_exit_code	ms_executor_destroy(struct s_ms_executor *executor);

//////////////////////////////////////////////////////////
////////////   interface used by ms_execute   ////////////
//////////////////////////////////////////////////////////

pid_t					ms_executor_fork(struct s_ms_executor *executor);

t_executor_exit_code	ms_executor_read_from_fd(int fd);

t_executor_exit_code	ms_executor_write_to_fd(int fd);

/**
 * @brief structural execution
*/

t_executor_exit_code	ms_executor_enact(struct s_ms_executor *executor, \
struct s_AST_node *node, struct s_ms *ms);

t_executor_exit_code	ms_executor_enact_pipe(\
struct s_ms_executor *executor, struct s_AST_node *node, struct s_ms *ms);

t_executor_exit_code	ms_executor_enact_ast(\
struct s_ms_executor *executor, struct s_AST_node *node, struct s_ms *ms);

/**
 * @brief ast node execution (used by ms_executor_ast)
*/

t_executor_exit_code	ms_executor_enact_assignment(\
struct s_ms_executor *executor, t_sb_vector *assignment, struct s_ms *ms);

t_executor_exit_code	ms_executor_enact_redirection_in(\
struct s_ms_executor *executor, t_AST_redirection_vector *redirection_in, \
struct s_ms *ms);

t_executor_exit_code	ms_executor_enact_redirection_out(\
struct s_ms_executor *executor, t_AST_redirection_vector *redirection_out, \
struct s_ms *ms);

t_executor_exit_code	ms_executor_enact_command(\
struct s_ms_executor *executor, t_sb_vector *command, struct s_ms *ms);

#endif