/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 01:45:33 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/13 04:38:59 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/expander/hashtable.h"
#include <stdio.h>

void	expander_hashtable_test1()
{
	struct s_ht	ht;

	ht_create(&ht, 10);
	ht_add(&ht, ft_strdup("key1"), ft_strdup("value1"));
	ht_add(&ht, ft_strdup("key2"), ft_strdup("value2"));
	ht_add(&ht, ft_strdup("key3"), ft_strdup("value3"));
	ht_add(&ht, ft_strdup("1key"), ft_strdup("1value"));
	ht_add(&ht, ft_strdup("2key"), ft_strdup("2value"));
	ht_add(&ht, ft_strdup("3key"), ft_strdup("3value"));
	ht_add(&ht, ft_strdup("4key"), ft_strdup("4value"));
	ht_add(&ht, ft_strdup("5key"), ft_strdup("5value"));
	ht_print(&ht);
	printf("got: %s\n", (char *) ht_get(&ht, "key1"));
	printf("got: %s\n", (char *) ht_get(&ht, "key2"));
	printf("got: %s\n", (char *) ht_get(&ht, "key3"));
	printf("got: %s\n", (char *) ht_get(&ht, "1key"));
	printf("got: %s\n", (char *) ht_get(&ht, "2key"));
	printf("got: %s\n", (char *) ht_get(&ht, "3key"));
	printf("got: %s\n", (char *) ht_get(&ht, "4key"));
	printf("got: %s\n", (char *) ht_get(&ht, "5key"));
	ht_destroy(&ht);
}
