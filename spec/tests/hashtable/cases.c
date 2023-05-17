/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 01:45:33 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/18 00:22:24 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "hashtable_test.h"

// hashtable can add

// hashtable can delete

// hashtable can get

// hashtable can update

void	expander_hashtable_test1()
{
	struct s_ht	ht;

	ht_create(&ht, 10);
	ht_print(&ht);
	ht_add(&ht, ft_strdup("key1"), ft_strdup("value1"));
	ht_add(&ht, ft_strdup("key2"), ft_strdup("value2"));
	ht_add(&ht, ft_strdup("key3"), ft_strdup("value3"));
	ht_add(&ht, ft_strdup("1key"), ft_strdup("1value"));
	ht_add(&ht, ft_strdup("2key"), ft_strdup("2value"));
	ht_add(&ht, ft_strdup("3key"), ft_strdup("3value"));
	ht_add(&ht, ft_strdup("4key"), ft_strdup("4value"));
	ht_add(&ht, ft_strdup("5key"), ft_strdup("5value"));
	printf("\n");
	ht_print(&ht);
	printf("got: %s\n", (char *) ht_get(&ht, "key1"));
	printf("got: %s\n", (char *) ht_get(&ht, "key2"));
	printf("got: %s\n", (char *) ht_get(&ht, "key3"));
	printf("got: %s\n", (char *) ht_get(&ht, "1key"));
	printf("got: %s\n", (char *) ht_get(&ht, "2key"));
	printf("got: %s\n", (char *) ht_get(&ht, "3key"));
	printf("got: %s\n", (char *) ht_get(&ht, "4key"));
	printf("got: %s\n", (char *) ht_get(&ht, "5key"));
	printf("\n");
	ht_del(&ht, "key1");
	ht_del(&ht, "key2");
	ht_del(&ht, "key3");
	ht_del(&ht, "2key");
	ht_del(&ht, "3key");
	ht_del(&ht, "4key");
	ht_add(&ht, ft_strdup("3key"), ft_strdup("im newwwwwwwwwww"));
	ht_add(&ht, ft_strdup("3key"), ft_strdup("im newwww222wwwwwww"));
	printf("got: %s\n", (char *) ht_get(&ht, "key1"));
	printf("got: %s\n", (char *) ht_get(&ht, "key2"));
	printf("got: %s\n", (char *) ht_get(&ht, "key3"));
	printf("got: %s\n", (char *) ht_get(&ht, "1key"));
	printf("got: %s\n", (char *) ht_get(&ht, "2key"));
	printf("jgot: %s\n", (char *) ht_get(&ht, "3key"));
	printf("got: %s\n", (char *) ht_get(&ht, "4key"));
	printf("got: %s\n", (char *) ht_get(&ht, "5key"));
	printf("\n");
	ht_print(&ht);
	ht_destroy(&ht);
}

void	expander_hashtable_test2()
{
	struct s_ht	ht;

	ht_create(&ht, 20);
	ht_add(&ht, ft_strdup("3key"), ft_strdup("3value"));
	ht_del(&ht, "3key");
	ht_print(&ht);
}

void	expander_hashtable_test3()
{
	struct s_ht	ht;
	unsigned char	key;
	unsigned char	total;
	unsigned char	key_start;

	key_start = 'a';
	total = 100;
	ht_create(&ht, 30);
	key = key_start;
	while (key < (key_start + total))
	{
		ht_add(&ht, ft_strdup((char[2]) {key, 0}), ft_strdup((char[3]) {key, '!', 0}));
		key++;
	}
	ht_print(&ht);
	key = key_start;
	while (key < (key_start + total))
	{
		printf("got: %s\n", (char *) ht_get(&ht, (char[2]) {key, 0}));
		key++;
	}
	printf("\n");
	ht_print(&ht);
	key = key_start;
	while (key < (key_start + (total / 2)))
	{
		ht_del(&ht, (char[2]) {key, 0});
		key++;
	}
	key = key_start;
	while (key < (key_start + total))
	{
		printf("got: %s\n", (char *) ht_get(&ht, (char[2]) {key, 0}));
		key++;
	}
	printf("\n");
	ht_print(&ht);
	ht_destroy(&ht);
}
