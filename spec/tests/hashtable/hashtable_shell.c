/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:45:26 by htsang            #+#    #+#             */
/*   Updated: 2023/05/18 08:29:32 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable_test.h"

struct s_ht	*hashtable_shell_init(void)
{
	struct s_ht	*ht;

	ht = malloc(sizeof(struct s_ht));
	if (!ht)
		return (NULL);
	if (ht_create(ht, 10))
	{
		free(ht);
		return (NULL);
	}
	return (ht);
}

t_tshell_status	hashtable_shell_execute_func2(struct s_ht *ht, struct s_tparser *tparser, \
int	(*func2)(struct s_ht *ht, const char *key, const void *value))
{
	char	*param[2];

	if (tparser_consume_n_parameters(tparser, 2, TSHELL_STRING, TSHELL_STRING))
		return (TSHELL_FAILURE);
	param[0] = tparser_read(tparser);
	param[1] = tparser_read(tparser);
	if (func2(ht, param[0], param[1]))
	{
		return (TSHELL_FAILURE);
	}
	ht_print(ht);
	return (TSHELL_SUCCESS);
}

t_tshell_status	hashtable_shell_execute_get(struct s_ht *ht, struct s_tparser *tparser)
{
	if (tparser_consume_exactly_one_parameter(tparser, TSHELL_STRING))
		return (TSHELL_FAILURE);
	printf("got: %s\n", (char *) ht_get(ht, tparser_read(tparser)));
	return (TSHELL_SUCCESS);
}

t_tshell_status	hashtable_shell_execute_del(struct s_ht *ht, struct s_tparser *tparser)
{
	if (tparser_consume_exactly_one_parameter(tparser, TSHELL_STRING))
		return (TSHELL_FAILURE);
	ht_del(ht, tparser_read(tparser));
	ht_print(ht);
	return (TSHELL_SUCCESS);
}

t_tshell_status	hashtable_shell(struct s_ht *ht, struct s_tparser *tparser)
{
	if (!tparser_match_string(tparser, "print"))
	{
		return (tshell_execute_printer(ht, tparser, (t_printer_func) ht_print));
	}
	if (!tparser_match_string(tparser, "add"))
	{
		return (hashtable_shell_execute_func2(ht, tparser, ht_add));
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
	return (TSHELL_SUCCESS);
}
