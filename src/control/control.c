/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 00:17:27 by htsang            #+#    #+#             */
/*   Updated: 2023/06/26 04:50:23 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/ctype.h"
#include "MINISHELL/minishell.h"

extern char	**environ;

int	ms_init(struct s_ms *ms)
{
	if ((ms_executor_init(&ms->executor) == PROGRAM_ERROR) || \
		ms_vars_init(&ms->vars) || \
		ms_vars_import(&ms->vars, environ) || \
		ms_vars_import_default_special(&ms->vars))
	{
		ms_vars_free(&ms->vars);
		return (EXIT_FAILURE);
	}
	ms->ast_root = NULL;
	ms->line = NULL;
	return (EXIT_SUCCESS);
}

void	ms_reset(struct s_ms *ms)
{
	ms_executor_reset(&ms->executor);
	if (ms->ast_root)
	{
		ast_node_free(ms->ast_root);
		ms->ast_root = NULL;
	}
	if (ms->line)
	{
		free(ms->line);
		ms->line = NULL;
	}
}

bool	ms_line_is_empty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

void	ms_free(struct s_ms *ms)
{
	ms_vars_free(&ms->vars);
	ms_executor_free(&ms->executor);
	if (ms->ast_root)
	{
		ast_node_free(ms->ast_root);
		ms->ast_root = NULL;
	}
	if (ms->line)
	{
		free(ms->line);
		ms->line = NULL;
	}
}
