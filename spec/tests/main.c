/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:spec/tests/main.c
/*   Created: 2022/10/29 14:52:46 by htsang            #+#    #+#             */
/*   Updated: 2023/05/13 04:55:32 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
========
/*   Created: 2023/05/29 12:49:43 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/01 15:25:08 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/execution/expander.h"
>>>>>>>> execution:src/execution/expander/match.c

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
