/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 01:38:36 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/20 03:52:46 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/hashtable.h"
#include <stdio.h>

void	ht_print(struct s_ht *ht)
{
	t_ht_index	i;

	i = 0;
	while (i < ht->capacity)
	{
		if (ht->entries[i].key)
			printf("%s: %s", ht->entries[i].key, (char *) ht->entries[i].value);
		else
			printf("EMPTY");
		if (ht->entries[i].deleted)
			printf(" (deleted)\n");
		else
			printf("\n");
		i++;
	}
	printf("\n");
}
