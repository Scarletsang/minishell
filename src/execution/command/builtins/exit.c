/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/07/04 13:26:00 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "MINISHELL/execution/command/builtins.h"
#include "LIBFT/general.h"
#include "MINISHELL/error_printer.h"

static bool	num_is_in_ll_range(long long value, int sign)
{
	if (value < 0)
	{
		if (sign == 1)
			return (false);
		if (sign == -1 && value != LLONG_MIN)
			return (false);
	}
	return (true);
}

static bool	is_valid_ll(char *str, long long *n)
{
	int			sign;

	sign = 1;
	if (!str || !*str)
		return (false);
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (false);
	while (ft_isdigit(*str))
	{
		*n = *n * 10 + (*str - '0');
		str++;
	}
	if (*str)
		return (false);
	if (!num_is_in_ll_range(*n, sign))
		return (false);
	*n = (long long)*n * sign;
	return (true);
}

static void	builtin_exit_with_no_arg(struct s_ms *ms)
{
	ms_free(ms);
	exit (ms->executor.last_exit_code);
}

t_ms_exit_code	ms_execute_builtin_exit(struct s_ms *ms, t_sb_vector *command)
{
	long long					n;
	struct s_ft_vector_iterator	vec_iter;

	printf("exit\n");
	if (command->size == 1)
		builtin_exit_with_no_arg(ms);
	n = 0;
	ft_vector_iterator_init(&vec_iter, command);
	ft_vector_iterator_next(&vec_iter);
	if (is_valid_ll(((t_ft_sb *)ft_vector_iterator_current(&vec_iter))->buffer, \
		&n) == false)
	{
		ms_free(ms);
		ms_error_printer_builtin("exit", NULL, "numeric argument required");
		exit (-1);
	}
	if (command->size > 2)
	{
		ms_error_printer_builtin("exit", NULL, "too many arguments");
		return (EC_FAILURE);
	}
	ms_free(ms);
	exit (n);
}
