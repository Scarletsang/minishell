/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:18:03 by htsang            #+#    #+#             */
/*   Updated: 2023/06/21 15:20:44 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdbool.h>
# include <unistd.h>
# include "LIBFT/vector.h"
# include "MINISHELL/execution/piper.h"
# include "MINISHELL/execution/vars.h"

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
	struct s_ms_piper		piper;
	struct s_ft_iostream	iostream;
	t_ft_vector				envp;
	int						stdin_fd;
	pid_t					last_child_pid;
};

t_executor_exit_code	ms_executor_init(struct s_ms_executor *executor);

t_executor_exit_code	ms_executor_reset(struct s_ms_executor *executor);

t_executor_exit_code	ms_executor_destroy(struct s_ms_executor *executor);

//////////////////////////////////////////////////////////
////////////   interface used by ms_execute   ////////////
//////////////////////////////////////////////////////////

pid_t					ms_executor_fork(struct s_ms_executor *executor);

t_executor_return_value	ms_executor_wait(struct s_ms_executor *executor);

t_executor_exit_code	ms_executor_redirect_from_file(const char *filename, \
int flags);

t_executor_exit_code	ms_executor_redirect_to_file(const char *filename, \
int flags);

t_executor_exit_code	ms_executor_redirect_from_heredoc(void);

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