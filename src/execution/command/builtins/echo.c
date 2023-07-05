/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/07/05 23:46:39 by sawang           ###   ########.fr       */
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

// static char	*ft_strchr_isspace(char *str, char *delimeter_set)
// {
// 	int	i;

// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] && !ft_strchr(delimeter_set, str[i]))
// 		i++;
// 	if (str[i])
// 		return (str + i);
// 	return (NULL);
// }

// static void	echo_print_sb_with_option_n(char *sb_buffer)
// {
// 	char	*ptr;

// 	if (!sb_buffer)
// 		return ;
// 	ptr = ft_strchr_isspace(sb_buffer, " \t\f\r\v");
// 	if (*(ptr + 1))
// 		ft_putstr_fd(ptr + 1, STDOUT_FILENO);
// }

// static void	echo_print_sb_vector(t_ft_vector_iterator *iterator)
// {
// 	while (!ft_vector_iterator_is_end(iterator))
// 	{
// 		ft_putstr_fd((char *) \
// 			((t_ft_sb *) ft_vector_iterator_current(iterator))->buffer, \
// 			STDOUT_FILENO);
// 		ft_vector_iterator_next(iterator);
// 		if (!ft_vector_iterator_is_end(iterator))
// 			ft_putchar_fd(' ', STDOUT_FILENO);
// 	}
// }

t_ms_exit_code	ms_execute_builtin_echo(struct s_ms *ms, t_sb_vector *command)
{
	t_ft_vector_iterator	iterator;
	bool					option_n;

	(void) ms;
	ft_vector_iterator_init(&iterator, command);
	ft_vector_iterator_next(&iterator);
	option_n = echo_with_option_n((char *) \
		((t_ft_sb *) ft_vector_iterator_current(&iterator))->buffer, "\0");
	if (option_n)
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
	if (!option_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EC_SUCCESS);
}
