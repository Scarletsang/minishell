/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iostream copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:25:51 by htsang            #+#    #+#             */
/*   Updated: 2023/06/17 17:09:07 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/iostream.h"

int	iostream_init(struct s_iostream *iostream)
{
	if (sb_init(&iostream->sb, IOSTREAM_BUFFER_SIZE))
		return (EXIT_FAILURE);
	sb_clipper_init(&iostream->clipper, &iostream->sb);
	return (EXIT_SUCCESS);
}

void	iostream_free(struct s_iostream *iostream)
{
	sb_free(&iostream->sb);
}
