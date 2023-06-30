/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:48:07 by htsang            #+#    #+#             */
/*   Updated: 2023/06/30 10:52:01 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/ctype.h"
#include "MINISHELL/execution.h"

static int	ms_strcmp_ignore_case(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (ft_isalpha(*s1) && ft_isalpha(*s2))
		{
			if (ft_tolower(*s1) != ft_tolower(*s2))
				break ;
		}
		else if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	return ((unsigned char) *s1 - (unsigned char) *s2);
}

enum e_ms_execution_mode	ms_execution_mode(t_sb_vector *command)
{
	char	*name;

	if (command->size == 0)
		return (MODE_NO_COMMAND);
	name = ((t_ft_sb *) command->buffer)->buffer;
	if (ms_strcmp_ignore_case(name, "echo") == 0)
		return (MODE_BUILTIN_ECHO);
	if (ms_strcmp_ignore_case(name, "cd") == 0)
		return (MODE_BUILTIN_CD);
	if (ms_strcmp_ignore_case(name, "pwd") == 0)
		return (MODE_BUILTIN_PWD);
	if (ms_strcmp_ignore_case(name, "unset") == 0)
		return (MODE_BUILTIN_UNSET);
	if (ms_strcmp_ignore_case(name, "export") == 0)
		return (MODE_BUILTIN_EXPORT);
	if (ms_strcmp_ignore_case(name, "env") == 0)
		return (MODE_BUILTIN_ENV);
	if (ms_strcmp_ignore_case(name, "exit") == 0)
		return (MODE_BUILTIN_EXIT);
	return (MODE_EXECUTABLE);
}
