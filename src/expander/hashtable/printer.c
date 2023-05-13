/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 01:38:36 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/13 06:42:23 by anthonytsan      ###   ########.fr       */
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
			printf("%s: %s %s\n", ht->items[i].key, \
				(char *) ht->items[i].value, ht->items[i].deleted ? "(deleted)" : "");
		else
			printf("EMPTY %s\n", ht->items[i].deleted ? "(deleted)" : "");
		i++;
	}
	printf("\n");
}
