/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/07/07 04:28:44 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "MINISHELL/execution/command/builtins.h"
#include "LIBFT/ctype.h"
#include "LIBFT/string.h"
#include "LIBFT/io.h"
#include "MINISHELL/error_printer.h"

static void	export_vars_print(const struct s_ms_vars *vars, \
	char *declare_prefix)
{
	size_t					i;
	struct s_ft_ht_entry	*entry;

	i = 0;
	while (i < vars->environment.capacity)
	{
		entry = ft_vector_get(&vars->environment, i);
		if (entry->key)
		{
			ft_putstr_fd(declare_prefix, STDOUT_FILENO);
			ft_putendl_fd((char *) entry->value.content, STDOUT_FILENO);
		}
		i++;
	}
}

static void	export_error_print_when_invalid_identifier(\
	char *key, t_ms_exit_code *exit_code)
{
	ms_error_printer_builtin("export", key, "not a valid identifier");
	*exit_code = EC_FAILURE;
}

static int	ms_vars_declare_export(struct s_ms_vars *vars, \
	t_ft_str_nt entry, t_ft_str entry_key)
{
	char	*equal_sign;

	equal_sign = ft_strchr(entry.content, '=');
	if (equal_sign == NULL && \
		(ft_ht_get(&vars->shell, entry_key).content != NULL))
		return (ms_vars_export(vars, entry_key));
	if (ms_vars_declare(vars, entry_key, entry) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ms_vars_export(vars, entry_key) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static t_ft_str	get_entry_key_from_str(char *value)
{
	t_ft_str	entry_slice;

	entry_slice.content = value;
	if (ft_strchr(value, '=') == NULL)
		entry_slice.size = ft_strlen(value);
	else
		entry_slice.size = ft_strchr(value, '=') - value;
	return (entry_slice);
}

t_ms_exit_code	ms_execute_builtin_export(struct s_ms *ms, t_sb_vector *command)
{
	t_ms_exit_code				exit_code;
	struct s_ft_vector_iterator	vec_iter;
	t_ft_str_nt					value;
	t_ft_str					key;

	if (command->size == 1)
		return (export_vars_print(&ms->vars, "declare -x "), EC_SUCCESS);
	exit_code = EC_SUCCESS;
	ft_vector_iterator_begin(&vec_iter, command);
	while (!ft_vector_iterator_next(&vec_iter))
	{
		value = (t_ft_str_nt){
			.content = \
				((t_ft_sb *)ft_vector_iterator_current(&vec_iter))->buffer,
			.size = ((t_ft_sb *)ft_vector_iterator_current(&vec_iter))->size
		};
		if (((char *)value.content)[0] == '\0')
			value = (t_ft_str_nt){NULL, 0};
		key = get_entry_key_from_str(value.content);
		if (!name_is_valid_indentifier(key.content, '='))
			export_error_print_when_invalid_identifier(key.content, &exit_code);
		else if (ms_vars_declare_export(&ms->vars, value, key) == EXIT_FAILURE)
			return (ms_error_printer_internal_error(), EC_FAILURE);
	}
	return (exit_code);
}
