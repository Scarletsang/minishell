/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:49:43 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/30 19:32:53 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/expander.h"

int	minishell_expander_match_any(t_sb_iterator *it, const char *set)
{
	size_t	i;
	char	current;

	i = 0;
	current = sb_iterator_current(it);
	while (set[i])
	{
		if (current == set[i])
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}
