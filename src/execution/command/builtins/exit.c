/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/07/03 16:44:07 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/execution/command/builtins.h"
#include "LIBFT/general.h"

t_ms_exit_code	ms_execute_builtin_exit(struct s_ms *ms, t_sb_vector *command)
{
	int							n;
	struct s_ft_vector_iterator	vec_iter;

	if (command->size == 1)
	{
		ms_free(ms);
		exit (ms->executor.last_exit_code);
	}
	n = 0;
	ft_vector_iterator_init(&vec_iter, command);
	ft_vector_iterator_next(&vec_iter);
	if (ms_atoi(((t_ft_sb *)ft_vector_iterator_current(&vec_iter))->buffer, &n) \
		== false)
	{
		ft_printf("exit\n");
		ms_error_printer_builtin("exit", NULL, "numeric argument required");
		ms_free(ms);
		exit (255);
	}
	if (command->size > 2)
	{
		ft_printf("exit\n");
		ms_error_printer_builtin("exit", NULL, "too many arguments");
		ms_free(ms);
		exit (EC_FAILURE);
	}
	exit (n);
}
