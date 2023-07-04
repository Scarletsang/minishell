/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/07/04 11:23:03 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "MINISHELL/execution/command/builtins.h"
#include "LIBFT/general.h"
#include "MINISHELL/error_printer.h"

	// 9223372036854775807

static bool	is_valid_ll(char *str, long long *n)
{
	int			sign;
	long long	value;

	sign = 1;
	if (!str || !*str)
		return (false);
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (false);
	value = 0;
	while (ft_isdigit(*str))
	{
		value = value * 10 + (*str - '0');
		str++;
	}
	if (*str)
		return (false);
	if (value < 0)
	{
		if (sign == 1)
			return (false);
		if (sign == -1 && value == LLONG_MIN)
			return (true);
		else
			return (false);
	}
	*n = (long long)value * sign;
	return (true);
}

t_ms_exit_code	ms_execute_builtin_exit(struct s_ms *ms, t_sb_vector *command)
{
	long long					n;
	struct s_ft_vector_iterator	vec_iter;

	if (command->size == 1)
	{
		ms_free(ms);
		exit (ms->executor.last_exit_code);
	}
	n = 0;
	ft_vector_iterator_init(&vec_iter, command);
	ft_vector_iterator_next(&vec_iter);
	if (is_valid_ll(((t_ft_sb *)ft_vector_iterator_current(&vec_iter))->buffer, &n) \
		== false)
	{
		printf("exit\n");
		ms_error_printer_builtin("exit", NULL, "numeric argument required");
		ms_free(ms);
		exit (255);
	}
	if (command->size > 2)
	{
		printf("exit\n");
		ms_error_printer_builtin("exit", NULL, "too many arguments");
		// ms_free(ms); // should we free ms here? different in child process or parent process?
		return (EC_FAILURE);
	}
	printf("exit\n");
	ms_free(ms);
	exit (n);
}
