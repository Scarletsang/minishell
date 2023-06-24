/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:24:47 by htsang            #+#    #+#             */
/*   Updated: 2023/06/24 01:30:31 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include "MINISHELL/parser/ast.h"
# include "MINISHELL/execution/vars.h"
# include "MINISHELL/execution/executor.h"

struct s_ms
{
	struct s_ms_vars		vars;
	struct s_ms_executor	executor;
	struct s_ast_node		*ast_root;
	char					*line;
};

int		ms_init(struct s_ms *ms);

void	ms_reset(struct s_ms *ms);

void	ms_free(struct s_ms *ms);

#endif