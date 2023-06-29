/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:10:15 by htsang            #+#    #+#             */
/*   Updated: 2023/06/29 03:35:11 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/executor.h"

char	**ms_executor_envp(struct s_ms_executor *executor)
{
	if (executor->envp.size == 0)
		return (NULL);
	return (executor->envp.buffer);
}

void	ms_executor_envp_reset(struct s_ms_executor *executor)
{
	executor->envp.size = 0;
}
