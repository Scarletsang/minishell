/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:10:43 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/01 02:18:27 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_test.h"

extern char **environ;

struct s_minishell_vars	*expander_shell_init(void)
{
	struct s_minishell_vars	*vars;

	vars = malloc(sizeof(struct s_minishell_vars));
	if (!vars)
		return (NULL);
	if (minishell_vars_init(vars))
	{
		free(vars);
		return (NULL);
	}
	if (minishell_vars_import(vars, environ))
	{
		minishell_vars_free(vars);
		free(vars);
		return (NULL);
	}
	return (vars);
}

t_tshell_status	expander_shell(struct s_minishell_vars *vars, \
struct s_tparser *tparser)
{
	t_sb	sb;

	if (sb_init(&sb, TSHELL_MAX_INPUT_SIZE / 16))
		return (TSHELL_FAILURE);
	if (sb_perform(&sb, sb_action_append(tparser->line)) || \
		minishell_expander(&sb, vars))
	{
		sb_free(&sb);
		return (TSHELL_FAILURE);
	}
	printf("%s\n", (char *) sb.buffer);
	sb_free(&sb);
	return (TSHELL_SUCCESS);
}

int	main(void)
{
	return (interact(\
		(t_init_func) expander_shell_init, \
		(t_program_func) expander_shell, \
		(t_free_func) minishell_vars_free));
}
