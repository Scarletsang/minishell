/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:18:03 by htsang            #+#    #+#             */
/*   Updated: 2023/06/09 20:57:29 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdlib.h>
# include <unistd.h>
# include "MINISHELL/minishell.h"
# include "MINISHELL/parser/ast.h"

////////////////////////////////////////////////
////////////   executor interface   ////////////
////////////////////////////////////////////////

typedef int	t_executor_exit_code;

enum	e_ms_executor_pipe
{
	PIPE1,
	PIPE2
};

struct s_ms_executor
{
	int						pipe1[2];
	int						pipe2[2];
	enum e_ms_executor_pipe	stdout_pipe;
	pid_t					last_child_pid;
};

void					ms_executor_init(struct s_ms_executor *executor);

int						ms_executor_pipe(struct s_ms_executor *executor);

pid_t					ms_executor_fork(struct s_ms_executor *executor);

t_executor_exit_code	ms_executor_wait(struct s_ms_executor *executor);

int						ms_executor_read_from_pipe(\
struct s_ms_executor *executor);

int						ms_executor_write_to_pipe(\
struct s_ms_executor *executor);

int						ms_executor_read_from_fd(int fd);

int						ms_executor_write_to_fd(int fd);

////////////////////////////////////////////////
///////////    private interface    ////////////
////////////////////////////////////////////////

int						*ms_executor_get_stdout_pipe(\
struct s_ms_executor *executor);

int						*ms_executor_get_stdin_pipe(\
struct s_ms_executor *executor);

////////////////////////////////////////////////////////////////
////////////   interface used by the ast iterator   ////////////
////////////////////////////////////////////////////////////////

int						ms_executor_enact_pipe(\
struct s_ms_executor *executor, struct s_AST_node *node, struct s_ms *ms);

int						ms_executor_enact_ast(\
struct s_ms_executor *executor, struct s_AST_node *node, struct s_ms *ms);

///////////////////////////////////////////////////////////////////////
////////////   private interface used by ms_executor_ast   ////////////
///////////////////////////////////////////////////////////////////////

int						ms_executor_enact_assignment(\
struct s_ms_executor *executor, t_sb_vector *assignment, struct s_ms *ms);

int						ms_executor_enact_redirection_in(\
struct s_ms_executor *executor, t_AST_redirection_vector *redirection_in, \
struct s_ms *ms);

int						ms_executor_enact_redirection_out(\
struct s_ms_executor *executor, t_AST_redirection_vector *redirection_out, \
struct s_ms *ms);

int						ms_executor_enact_command(\
struct s_ms_executor *executor, t_sb_vector *command, struct s_ms *ms);

#endif