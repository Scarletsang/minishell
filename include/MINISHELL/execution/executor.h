/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:18:03 by htsang            #+#    #+#             */
/*   Updated: 2023/07/03 16:05:19 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "LIBFT/iostream.h"
# include "LIBFT/vector.h"
# include "MINISHELL/execution/vars.h"
# include "MINISHELL/status_code.h"
# include "MINISHELL/execution/piper.h"

# ifndef HEREDOC_FILENAME
#  define HEREDOC_FILENAME "./.minishell_heredoc.tmp"
# endif

////////////////////////////////////////////////
////////////   executor interface   ////////////
////////////////////////////////////////////////

struct s_ms_executor
{
	struct s_ms_piper		piper;
	struct s_ft_iostream	heredoc;
	t_ft_vector				envp;
	int						stdin_fd;
	int						stdout_fd;
	t_ms_exit_code			last_exit_code;
	pid_t					last_child_pid;
};

t_ms_status		ms_executor_init(struct s_ms_executor *executor);

void			ms_executor_reset(struct s_ms_executor *executor);

t_ms_status		ms_executor_free(struct s_ms_executor *executor);

//////////////////////////////////////////////////////////
////////////   interface used by ms_execute   ////////////
//////////////////////////////////////////////////////////

pid_t			ms_executor_fork(struct s_ms_executor *executor);

t_ms_exit_code	ms_executor_wait(struct s_ms_executor *executor);

t_ms_status		ms_executor_redirect_from_file(struct s_ms_executor *executor, \
const char *filename, int flags);

t_ms_status		ms_executor_redirect_to_file(struct s_ms_executor *executor, \
const char *filename, int flags);

t_ms_status		ms_executor_reset_stdin_stdout(struct s_ms_executor *executor);

t_ms_status		ms_executor_open_heredoc(\
struct s_ms_executor *executor, int *fd);

t_ms_status		ms_executor_redirect_from_heredoc(int opened_heredoc_fd);

////////////////////////////////////////////
////////////   envp interface   ////////////
////////////////////////////////////////////

char			**ms_executor_envp(struct s_ms_executor *executor);

void			ms_executor_envp_reset(struct s_ms_executor *executor);

t_ms_status		ms_executor_envp_set(struct s_ms_executor *executor, \
char *pair);

const char		*ms_executor_envp_get(struct s_ms_executor *executor, \
const char *key);

/**
 * @brief Copy all entries from the environment database to the executor's
 * envp, which stores the envp expected by the execve syscall. It will only
 * copy the entries if the environment has been changed since the last call to
 * this function.
*/
t_ms_status		ms_executor_envp_import_from_environment(\
struct s_ms_executor *executor, struct s_ms_vars *vars);

#endif
