/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:45:26 by htsang            #+#    #+#             */
/*   Updated: 2023/06/24 02:05:02 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/hashtable.h"
#include "hashtable_test.h"

t_ft_ht	*hashtable_shell_init(void)
{
	t_ft_ht	*ht;

	ht = malloc(sizeof(t_ft_ht));
	if (!ht)
		return (NULL);
	if (ft_ht_init(ht, 5))
	{
		free(ht);
		return (NULL);
	}
	return (ht);
}

t_tshell_status	hashtable_shell_execute_func2(t_ft_ht *ht, struct s_tparser *tparser, \
const struct s_ft_ht_entry	*(*func2)(t_ft_ht *ht, t_ft_str key, t_ft_object v, t_ft_ht_entry_cleaner cleaner))
{
	char	*param[2];

	if (tparser_consume_n_parameters(tparser, 2, TSHELL_STRING, TSHELL_STRING))
		return (TSHELL_FAILURE);
	param[0] = tparser_read(tparser);
	param[1] = tparser_read(tparser);
	if (!func2(ht, (t_ft_str) {.content = param[0], .size = strlen(param[0])}, (t_ft_str) {.content = param[1], .size = strlen(param[1])}, free))
	{
		return (TSHELL_FAILURE);
	}
	ft_ht_print(ht);
	return (TSHELL_SUCCESS);
}

t_tshell_status	hashtable_shell_execute_get(t_ft_ht *ht, struct s_tparser *tparser)
{
	if (tparser_consume_exactly_one_parameter(tparser, TSHELL_STRING))
		return (TSHELL_FAILURE);
	t_ft_str str;
	str.content = tparser_read(tparser);
	str.size = strlen(str.content);
	t_ft_str result = ft_ht_get(ht, str);
	printf("got: %.*s\n", (int) result.size, (char*) result.content);
	return (TSHELL_SUCCESS);
}

t_tshell_status	hashtable_shell_execute_del(t_ft_ht *ht, struct s_tparser *tparser)
{
	if (tparser_consume_exactly_one_parameter(tparser, TSHELL_STRING))
		return (TSHELL_FAILURE);
	t_ft_str str;
	str.content = tparser_read(tparser);
	str.size = strlen(str.content);
	ft_ht_delete(ht, str);
	ft_ht_print(ht);
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

t_tshell_status	hashtable_shell(t_ft_ht *ht, struct s_tparser *tparser)
{
	if (!tparser_match_string(tparser, "help"))
	{
		return (hashtable_shell_print_mannual());
	}
	if (!tparser_match_string(tparser, "print"))
	{
		return (tshell_execute_printer(ht, tparser, (t_printer_func) ft_ht_print));
	}
	if (!tparser_match_string(tparser, "add"))
	{
		return (hashtable_shell_execute_func2(ht, tparser, ft_ht_set));
	}
	if (!tparser_match_string(tparser, "update"))
	{
		return (hashtable_shell_execute_func2(ht, tparser, ft_ht_update));
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
	return (interact(\
		(t_init_func) hashtable_shell_init, \
		(t_program_func) hashtable_shell, \
		(t_free_func) ft_ht_free));
}
