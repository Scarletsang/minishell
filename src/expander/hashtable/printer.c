/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 01:38:36 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/13 04:37:22 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/expander/hashtable.h"
#include <stdio.h>

void	ht_print(struct s_ht *ht)
{
	t_ht_index	i;

	i = 0;
	while (i < ht->capacity)
	{
		if (ht->items[i].key)
			printf("%s: %s\n", ht->items[i].key, \
				(char *) ht->items[i].value);
		else
			printf("EMPTY\n");
		i++;
	}
}
