/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iostream.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:56:31 by htsang            #+#    #+#             */
/*   Updated: 2023/06/16 22:40:46 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOSTREAM_H
# define IOSTREAM_H

# include <unistd.h>
# include "MINISHELL/slice.h"
# include "MINISHELL/stringbuilder.h"
# include "MINISHELL/stringbuilder/clipper.h"

# ifndef IOSTREAM_BUFFER_SIZE
#  define IOSTREAM_BUFFER_SIZE 20
# endif

struct s_ms_iostream
{
	t_sb				sb;
	struct s_sb_clipper	clipper;
	ssize_t				read_size;
};

int		iostream_init(struct s_ms_iostream *iostream);

int		iostream_read(struct s_ms_iostream *iostream, int fd);

int		iostream_read_until(struct s_ms_iostream *iostream, int fd, \
const char *end_match);

void	iostream_free(struct s_ms_iostream *iostream);

#endif