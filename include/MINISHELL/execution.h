/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:21:44 by htsang            #+#    #+#             */
/*   Updated: 2023/06/28 10:33:23 by htsang           ###   ########.fr       */
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

enum e_ms_execution_mode	ms_execution_mode(t_sb_vector *command);

/**
 * @brief structural execution
*/

t_ms_exit_code				ms_execute_ast(struct s_ms *ms, \
struct s_ast_node *root);

t_ms_status					ms_execute_pipe(struct s_ms *ms, \
struct s_ast_node *pipe);

#endif