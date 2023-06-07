/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:18:03 by htsang            #+#    #+#             */
/*   Updated: 2023/06/07 08:52:30 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

struct s_minishell_executor
{
	int				pipe1[2];
	int				pipe2[2];
	int				stdin_fd;
	int				stdout_fd;
	char *const*	cmd;
};

void	minishell_executor_init(struct s_minishell_executor *executor);



void	minishell_executor_free(struct s_minishell_executor *executor);
// handle <  redirection (stdin)
// handle << heredoc
// handle >  redirection (stdout)
// handle >> redirection appends (stdout)
// handle | piping
// handle = assignment

#endif