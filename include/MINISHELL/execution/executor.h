/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:18:03 by htsang            #+#    #+#             */
/*   Updated: 2023/06/17 18:21:59 by htsang           ###   ########.fr       */
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

# ifndef HEREDOC_FILENAME
#  define HEREDOC_FILENAME "./.minishell_heredoc.tmp"
# endif

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
	t_vector			envp;
	int					stdin_fd;
	int					heredoc_fd;
	bool				heredoc_fd_opened;
	pid_t				last_child_pid;
};

t_executor_exit_code	ms_executor_init(struct s_ms_executor *executor);

t_executor_exit_code	ms_executor_close_heredoc_fd(\
struct s_ms_executor *executor);

t_executor_exit_code	ms_executor_destroy(struct s_ms_executor *executor);

//////////////////////////////////////////////////////////
////////////   interface used by ms_execute   ////////////
//////////////////////////////////////////////////////////

pid_t					ms_executor_fork(struct s_ms_executor *executor);

t_executor_return_value	ms_executor_wait(struct s_ms_executor *executor);

t_executor_exit_code	ms_executor_read_from_fd(int fd);

t_executor_exit_code	ms_executor_write_to_fd(int fd);

////////////////////////////////////////////
////////////   envp interface   ////////////
////////////////////////////////////////////

t_executor_exit_code	ms_executor_envp_set(struct s_ms_executor *executor, \
char *pair);

char					**ms_executor_envp_get(struct s_ms_executor *executor);

/**
 * @brief Copy all entries from the environment database to the executor's
 * envp, which stores the envp expected by the execve syscall. It will only
 * copy the entries if the environment has been changed since the last call to
 * this function.
*/
t_executor_exit_code	ms_executor_envp_import_from_environment(\
struct s_ms_executor *executor, struct s_ms_vars *vars);

void					ms_executor_envp_reset(struct s_ms_executor *executor);

#endif