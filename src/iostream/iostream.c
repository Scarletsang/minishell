/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iostream.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:25:51 by htsang            #+#    #+#             */
/*   Updated: 2023/06/16 23:20:38 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/iostream.h"
#include "MINISHELL/stringbuilder/sb_iterator.h"

int	iostream_init(struct s_ms_iostream *iostream)
{
	if (sb_init(&iostream->sb, IOSTREAM_BUFFER_SIZE))
		return (EXIT_FAILURE);
	sb_clipper_init(&iostream->clipper, &iostream->sb);
	return (EXIT_SUCCESS);
}

int	iostream_read(struct s_ms_iostream *iostream, int fd)
{
	iostream->read_size = read(fd, iostream->sb.buffer, IOSTREAM_BUFFER_SIZE);
	if (iostream->read_size < 0)
		return (EXIT_FAILURE);
	iostream->clipper.rbound += (size_t) iostream->read_size;
	return (EXIT_SUCCESS);
}

static int iostream_find_match(struct s_ms_iostream *iostream, \
char **match, char *reset)
{
	while (iostream->clipper.lbound < iostream->clipper.rbound)
	{
		if (sb_clipper_at_lbound(&iostream->clipper) == **match)
		{
			*match++;
			if (!**match)
				return (EXIT_SUCCESS);
		}
		else
		{
			*match = reset;
			if (sb_clipper_move_lbound(&iostream->clipper))
				return (EXIT_FAILURE);
		}
		sb_clipper_move_lbound(&iostream->clipper);
	}
	return (EXIT_FAILURE);
}

int	iostream_read_until(struct s_ms_iostream *iostream, int fd, \
const char *end_match)
{
	const char	*match;
	const char	*content;

	if (iostream_read(iostream, fd))
		return (EXIT_FAILURE);
	match = end_match;
	while (iostream->clipper.lbound < iostream->clipper.rbound)
	{
		if (sb_clipper_at_lbound(&iostream->clipper) == *match)
		{
			match++;
			if (!*match)
				break ;
		}
		else
			match = end_match;
		sb_clipper_move_lbound(&iostream->clipper);
	}
}

void	iostream_free(struct s_ms_iostream *iostream)
{
	sb_free(&iostream->sb);
}
