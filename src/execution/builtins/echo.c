/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/06/24 03:28:19 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "LIBFT/io.h"
#include "MINISHELL/execution/builtins.h"

int	ms_execute_builtin_echo(struct s_ms *ms, t_sb_vector *command)
{
	t_ft_vector_iterator	iterator;

	(void) ms;
	ft_vector_iterator_init(&iterator, command);
	ft_vector_iterator_next(&iterator);
	while (!ft_vector_iterator_is_end(&iterator))
	{
		ft_putstr_fd((char *) \
			((t_ft_sb *) ft_vector_iterator_current(&iterator))->buffer, \
			STDOUT_FILENO);
		ft_vector_iterator_next(&iterator);
		if (!ft_vector_iterator_is_end(&iterator))
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (EC_SUCCESS);
}
