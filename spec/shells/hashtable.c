/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:45:26 by htsang            #+#    #+#             */
/*   Updated: 2023/05/24 12:40:14 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable_test.h"

t_ht	*hashtable_shell_init(void)
{
	t_ht	*ht;

	ht = malloc(sizeof(t_ht));
	if (!ht)
		return (NULL);
	if (ht_init(ht, 5))
	{
		free(ht);
		return (NULL);
	}
	return (ht);
}

t_tshell_status	hashtable_shell_execute_func2(t_ht *ht, struct s_tparser *tparser, \
int	(*func2)(t_ht *ht, const char *key, const void *value, t_ht_entry_cleaner func))
{
	char	*param[2];

	if (tparser_consume_n_parameters(tparser, 2, TSHELL_STRING, TSHELL_STRING))
		return (TSHELL_FAILURE);
	param[0] = tparser_read(tparser);
	param[1] = tparser_read(tparser);
	if (func2(ht, param[0], param[1], free))
	{
		return (TSHELL_FAILURE);
	}
	ht_print(ht);
	return (TSHELL_SUCCESS);
}

t_tshell_status	hashtable_shell_execute_get(t_ht *ht, struct s_tparser *tparser)
{
	if (tparser_consume_exactly_one_parameter(tparser, TSHELL_STRING))
		return (TSHELL_FAILURE);
	printf("got: %s\n", (char *) ht_get(ht, tparser_read(tparser)));
	return (TSHELL_SUCCESS);
}

t_tshell_status	hashtable_shell_execute_del(t_ht *ht, struct s_tparser *tparser)
{
	if (tparser_consume_exactly_one_parameter(tparser, TSHELL_STRING))
		return (TSHELL_FAILURE);
	ht_del(ht, tparser_read(tparser));
	ht_print(ht);
	return (TSHELL_SUCCESS);
}

t_tshell_status	hashtable_shell_print_mannual(void)
{
	printf("%-23s: Print the hash table\n", "print");
	printf("%-23s: Add an entry to the hash table\n", "add key value");
	printf("%-23s: Set a new value of an existing key\n", "update key value");
	printf("%-23s: Get value of a key\n", "get key");
	printf("%-23s: Delete an entry using a key\n", "del key");
	return (TSHELL_SUCCESS);
}

t_tshell_status	hashtable_shell(t_ht *ht, struct s_tparser *tparser)
{
	if (!tparser_match_string(tparser, "help"))
	{
		return (hashtable_shell_print_mannual());
	}
	if (!tparser_match_string(tparser, "print"))
	{
		return (tshell_execute_printer(ht, tparser, (t_printer_func) ht_print));
	}
	if (!tparser_match_string(tparser, "add"))
	{
		return (hashtable_shell_execute_func2(ht, tparser, ht_set));
	}
	if (!tparser_match_string(tparser, "update"))
	{
		return (hashtable_shell_execute_func2(ht, tparser, ht_update));
	}
	if (!tparser_match_string(tparser, "get"))
	{
		return (hashtable_shell_execute_get(ht, tparser));
	}
	if (!tparser_match_string(tparser, "del"))
	{
		return (hashtable_shell_execute_del(ht, tparser));
	}
	return (TSHELL_FAILURE);
}

int	main(void)
{
	interact(\
		(t_init_func) hashtable_shell_init, \
		(t_program_func) hashtable_shell, \
		(t_free_func) ht_free);
	return (0);
}
