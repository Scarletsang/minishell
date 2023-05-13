/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 01:38:36 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/13 11:23:42 by htsang           ###   ########.fr       */
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
			printf("%s: %s", ht->items[i].key, (char *) ht->items[i].value);
		else
			printf("EMPTY");
		if (ht->items[i].deleted)
			printf(" (deleted)\n");
		else
			printf("\n");
		i++;
	}
	printf("\n");
}
