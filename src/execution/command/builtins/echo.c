/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 01:02:19 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "LIBFT/io.h"
#include "MINISHELL/execution/command/builtins.h"

t_ms_exit_code	ms_execute_builtin_echo(struct s_ms *ms, t_sb_vector *command)
{
	t_ft_vector_iterator	iterator;

	(void) ms;
	ft_vector_iterator_init(&iterator, command);
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
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (EC_SUCCESS);
}
