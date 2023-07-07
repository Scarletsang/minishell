/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 12:11:56 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "LIBFT/io.h"
#include "LIBFT/ctype.h"
#include "LIBFT/general.h"
#include "MINISHELL/execution/command/builtins.h"

static bool	echo_with_option_n(char *arg, char *delimeter_set)
{
	int	i;

	if (!arg)
		return (false);
	if (arg[0] != '-')
		return (false);
	if (arg[1] == '\0')
		return (false);
	i = 1;
	while (arg[i] && !ft_strchr(delimeter_set, arg[i]))
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

t_ms_exit_code	ms_execute_builtin_echo(struct s_ms *ms, t_sb_vector *command)
{
	t_ft_vector_iterator	iterator;
	bool					option_n;

	(void) ms;
	ft_vector_iterator_begin(&iterator, command);
	ft_vector_iterator_next(&iterator);
	option_n = echo_with_option_n((char *) \
		((t_ft_sb *) ft_vector_iterator_current(&iterator))->buffer, "\0");
	if (option_n)
		ft_vector_iterator_next(&iterator);
	while (!iterator.is_end)
	{
		ft_putstr_fd((char *) \
			((t_ft_sb *) ft_vector_iterator_current(&iterator))->buffer, \
			STDOUT_FILENO);
		ft_vector_iterator_next(&iterator);
		if (!iterator.is_end)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!option_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EC_SUCCESS);
}
