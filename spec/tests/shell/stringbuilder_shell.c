/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder_shell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:45:26 by htsang            #+#    #+#             */
/*   Updated: 2023/05/23 13:35:23 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "stringbuilder_test.h"

t_sb	*stringbuilder_shell_init(void)
{
	t_sb	*sb;

	sb = malloc(sizeof(t_sb));
	if (!sb)
		return (NULL);
	if (sb_init(sb, 20))
	{
		free(sb);
		return (NULL);
	}
	return (sb);
}

void	sb_print(t_sb *sb)
{
	printf("%s\n", (char *) sb->buffer);
}

t_tshell_status	stringbuilder_shell_execute_append(t_sb *sb, \
struct s_tparser *tparser)
{
	void	*param[2];

	if (tparser_consume_one_parameter(tparser, TSHELL_STRING))
		return (TSHELL_FAILURE);
	param[0] = tparser_read(tparser);
	if (tparser_consume_exactly_one_parameter(tparser, TSHELL_INT))
	{
		if (sb_perform(sb, sb_action_append(param[0])))
			return (TSHELL_FAILURE);
	}
	else
	{
		param[1] = tparser_read(tparser);
		if (sb_perform(sb, \
			sb_action_append_len(\
				param[0], \
				*(unsigned int *) param[1])))
			return (TSHELL_FAILURE);
	}
	sb_print(sb);
	return (TSHELL_SUCCESS);
}

t_tshell_status	stringbuilder_shell_execute_insert(t_sb *sb, \
struct s_tparser *tparser)
{
	void	*param[3];

	if (tparser_consume_n_parameters(tparser, 2, TSHELL_STRING, TSHELL_INT))
		return (TSHELL_FAILURE);
	param[0] = tparser_read(tparser);
	param[1] = tparser_read(tparser);
	if (tparser_consume_exactly_one_parameter(tparser, TSHELL_INT))
	{
		if (sb_perform(sb, \
			sb_action_insert(\
				param[0], \
				*(unsigned int *) param[1])))
			return (TSHELL_FAILURE);
	}
	else
	{
		param[2] = tparser_read(tparser);
		if (sb_perform(sb, \
			sb_action_insert_len(\
				param[0], \
				*(unsigned int *) param[1], \
				*(unsigned int *) param[2])))
			return (TSHELL_FAILURE);
	}
	sb_print(sb);
	return (TSHELL_SUCCESS);
}

t_tshell_status	stringbuilder_shell_execute_delete(t_sb *sb, \
struct s_tparser *tparser)
{
	void	*param[2];

	if (tparser_consume_n_parameters(tparser, 2, TSHELL_INT, TSHELL_INT) || \
		tparser_match_char(tparser, '\0'))
		return (TSHELL_FAILURE);
	param[0] = tparser_read(tparser);
	param[1] = tparser_read(tparser);
	if (sb_perform(sb, \
		sb_action_delete(\
			*(unsigned int *) param[0], \
			*(unsigned int *) param[1])))
		return (TSHELL_FAILURE);
	sb_print(sb);
	return (TSHELL_SUCCESS);
}

t_tshell_status	stringbuilder_shell_execute_replace(t_sb *sb, \
struct s_tparser *tparser)
{
	void	*param[4];

	if (tparser_consume_n_parameters(tparser, 3, TSHELL_STRING, TSHELL_INT, TSHELL_INT))
		return (TSHELL_FAILURE);
	param[0] = tparser_read(tparser);
	param[1] = tparser_read(tparser);
	param[2] = tparser_read(tparser);
	if (tparser_consume_exactly_one_parameter(tparser, TSHELL_INT))
	{
		if (sb_perform(sb, \
			sb_action_replace(\
				param[0], \
				*(unsigned int *) param[1], \
				*(unsigned int *) param[2])))
			return (TSHELL_FAILURE);
	}
	else
	{
		param[3] = tparser_read(tparser);
		if (sb_perform(sb, \
			sb_action_replace_len(\
				param[0], \
				*(unsigned int *) param[1], \
				*(unsigned int *) param[2], \
				*(unsigned int *) param[3])))
			return (TSHELL_FAILURE);
	}
	sb_print(sb);
	return (TSHELL_SUCCESS);
}

// print
// append str
// append str len
// insert str at
// insert str len at
// delete start len
// replace str at len
// replace str len at len

t_tshell_status	stringbuilder_shell_print_mannual(void)
{
	printf("%-23s: Print the string buffer\n", "print");
	printf("%-23s: Append a string to the end of the buffer. Optionally, append only a particular length of the string\n", "append str [str_len]");
	printf("%-23s: Insert a string at a particular index\n", "insert str at");
	printf("%-23s: Delete a particular length of the string from a particular index\n", "delete start len");
	printf("%-23s: Replace a particular length of the string from a particular index with a string\n", "replace str at len");
	printf("%-23s: Replace a particular length of the string from a particular index with a particular length of a string\n", "replace str len at len");
	return (TSHELL_SUCCESS);
}

t_tshell_status	stringbuilder_shell(t_sb *sb, struct s_tparser *tparser)
{
	if (!tparser_match_string(tparser, "help"))
	{
		return (stringbuilder_shell_print_mannual());
	}
	if (!tparser_match_string(tparser, "print"))
	{
		return (tshell_execute_printer(sb, tparser, (t_printer_func) sb_print));
	}
	if (!tparser_match_string(tparser, "append"))
	{
		return (stringbuilder_shell_execute_append(sb, tparser));
	}
	if (!tparser_match_string(tparser, "insert"))
	{
		return (stringbuilder_shell_execute_insert(sb, tparser));
	}
	if (!tparser_match_string(tparser, "delete"))
	{
		return (stringbuilder_shell_execute_delete(sb, tparser));
	}
	if (!tparser_match_string(tparser, "replace"))
	{
		return (stringbuilder_shell_execute_replace(sb, tparser));
	}
	return (TSHELL_SUCCESS);
}

int	main(void)
{
	interact(\
		(t_init_func) stringbuilder_shell_init, \
		(t_program_func) stringbuilder_shell, \
		(t_free_func) sb_free);
	return (0);
}