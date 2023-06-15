/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:21:44 by htsang            #+#    #+#             */
/*   Updated: 2023/06/15 19:33:25 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "MINISHELL/execution/executor.h"

t_executor_return_value	ms_execute(struct s_ast_node *node, struct s_ms *ms);

#endif