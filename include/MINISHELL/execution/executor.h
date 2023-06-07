/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:18:03 by htsang            #+#    #+#             */
/*   Updated: 2023/06/07 18:49:29 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "MINISHELL/minishell.h"
# include "MINISHELL/parser/ast.h"

////////////////////////////////////////////////
////////////   executor interface   ////////////
////////////////////////////////////////////////

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
};

void	ms_executor_init(struct s_ms_executor *executor);

void	ms_executor_free(struct s_ms_executor *executor);

int		ms_executor_read_from_pipe(struct s_ms_executor *executor);

int		ms_executor_write_to_pipe(struct s_ms_executor *executor);

int		ms_executor_read_from_fd(int fd);

int		ms_executor_write_to_fd(int fd);

////////////////////////////////////////////////////////////////
////////////   interface used by the ast iterator   ////////////
////////////////////////////////////////////////////////////////

int		ms_executor_pipe(struct s_ms_executor *executor, \
struct s_AST_node *node, struct s_ms *ms);

int		ms_executor_ast(struct s_ms_executor *executor, \
struct s_AST_node *node, struct s_ms *ms);

///////////////////////////////////////////////////////////////////////
////////////   private interface used by ms_executor_ast   ////////////
///////////////////////////////////////////////////////////////////////

int		ms_executor_assignment(struct s_ms_executor *executor, \
t_sb_vector *assignment, struct s_ms *ms);

int		ms_executor_redirection_in(struct s_ms_executor *executor, \
t_AST_redirection_vector *redirection_in, struct s_ms *ms);

int		ms_executor_redirection_out(struct s_ms_executor *executor, \
t_AST_redirection_vector *redirection_out, struct s_ms *ms);

int		ms_executor_command(struct s_ms_executor *executor, \
t_sb_vector *command, struct s_ms *ms);

#endif