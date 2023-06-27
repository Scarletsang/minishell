/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:10:43 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/24 02:20:33 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_test.h"

extern char **environ;

struct s_ms_vars	*expander_shell_init(void)
{
	struct s_ms_vars	*vars;

	vars = malloc(sizeof(struct s_ms_vars));
	if (!vars)
		return (NULL);
	if (ms_vars_init(vars))
	{
		free(vars);
		return (NULL);
	}
	if (ms_vars_import(vars, environ))
	{
		ms_vars_free(vars);
		free(vars);
		return (NULL);
	}
	return (vars);
}

t_tshell_status	expander_shell(struct s_ms_vars *vars, \
struct s_tparser *tparser)
{
	t_ft_sb	sb;

	if (ft_sb_init(&sb, TSHELL_MAX_INPUT_SIZE / 16))
		return (TSHELL_FAILURE);
	if (ft_sb_perform(&sb, ft_sb_action_append(tparser->line)) || \
		ms_expander(&sb, vars))
	{
		ft_sb_free(&sb);
		return (TSHELL_FAILURE);
	}
	printf("%s\n", (char *) sb.buffer);
	ft_sb_free(&sb);
	return (TSHELL_SUCCESS);
}

int	main(void)
{
	return (interact(\
		(t_init_func) expander_shell_init, \
		(t_program_func) expander_shell, \
		(t_free_func) ms_vars_free));
}
