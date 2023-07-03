/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/07/03 14:28:38 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "MINISHELL/execution/command/builtins.h"
#include "LIBFT/ctype.h"
#include "LIBFT/string.h"
#include "MINISHELL/error_printer.h"

static bool	export_name_is_valid_indentifier(char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (false);
	while (*name && *name != '=')
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
		name++;
	}
	return (true);
}

void	ms_exported_vars_print(const struct s_ms_vars *vars, \
	char *declare_prefix)
{
	size_t					i;
	struct s_ft_ht_entry	*entry;

	i = 0;
	while (i < vars->environment.capacity)
	{
		entry = ft_vector_get(&vars->environment, i);
		if (entry->key)
			printf("%s %s\n", declare_prefix, (char *) entry->value);
		i++;
	}
}

static int	ms_vars_declare_export(struct s_ms_vars *vars, \
	const char *entry, const char *entry_key)
{
	char	*equal_sign;

	equal_sign = ft_strchr(entry, '=');
	if (equal_sign == NULL)
	{
		if (ft_ht_get(&vars->shell, entry_key) == NULL)
		{
			if (ms_vars_declare(vars, entry_key, entry) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (ms_vars_export(vars, entry_key) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		if (ms_vars_declare(vars, entry_key, entry) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ms_vars_export(vars, entry_key) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
}

char	*get_entry_key_from_str(char *value)
{
	t_ft_slice	entry_slice;
	char		*entry_key;

	entry_slice.content = value;
	if (ft_strchr(value, '=') == NULL)
		entry_slice.size = ft_strlen(value);
	else
		entry_slice.size = ft_strchr(value, '=') - value;
	entry_key = ft_string_slice_to_cstring(entry_slice);
	return (entry_key);
}

t_ms_exit_code	ms_execute_builtin_export(struct s_ms *ms, t_sb_vector *command)
{
	t_ms_exit_code				exit_code;
	struct s_ft_vector_iterator	vec_iter;
	char						*value;
	char						*key;

	if (command->size == 1)
		return (ms_exported_vars_print(&ms->vars, "declare -x"), EC_SUCCESS);
	exit_code = EC_SUCCESS;
	ft_vector_iterator_init(&vec_iter, command);
	ft_vector_iterator_next(&vec_iter);
	while (!ft_vector_iterator_is_end(&vec_iter))
	{
		value = ((t_ft_sb *)ft_vector_iterator_current(&vec_iter))->buffer;
		key = get_entry_key_from_str(value);
		if (!export_name_is_valid_indentifier(key))
		{
			ms_error_printer_builtin("export", key, "not a valid identifier");
			exit_code = EC_FAILURE;
			free(key);
			ft_vector_iterator_next(&vec_iter);
			continue ;
		}
		if (ms_vars_declare_export(&ms->vars, value, key) == EXIT_FAILURE)
			return (ms_error_printer_internal_error(), free(key), EC_FAILURE);
		ft_vector_iterator_next(&vec_iter);
	}
	return (free(key), exit_code);
}
