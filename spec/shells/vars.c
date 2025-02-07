/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:27:13 by htsang            #+#    #+#             */
/*   Updated: 2023/06/24 02:01:01 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vars_test.h"

extern char **environ;

struct s_ms_vars	*vars_shell_init(void)
{
	struct s_ms_vars	*vars;

	vars = malloc(sizeof(struct s_ms_vars));
	if (!vars)
		return (NULL);
	if (ms_vars_init(vars))
	{
		free(vars);
		return (NULL);
	}
	return (vars);
}

// import
// assign var name
// export var name
// export var
// export
// unset var
// env

t_tshell_status	vars_shell_execute_import(struct s_ms_vars *vars, \
struct s_tparser *tparser)
{
	(void) tparser;
	if (ms_vars_import(vars, environ))
		return (TSHELL_FAILURE);
	return (TSHELL_SUCCESS);
}

t_tshell_status	vars_shell_execute_assign(struct s_ms_vars *vars, \
struct s_tparser *tparser)
{
	char	*param[2];

	if (tparser_consume_n_parameters(tparser, 2, TSHELL_STRING, TSHELL_STRING))
		return (TSHELL_FAILURE);
	param[0] = tparser_read(tparser);
	param[1] = tparser_read(tparser);
	if (!ms_vars_database_set(&vars->shell, ft_str_from_cstring(param[0]), ft_str_from_cstring(param[1])))
		return (TSHELL_FAILURE);
	return (TSHELL_SUCCESS);
}

t_tshell_status	vars_shell_execute_export(struct s_ms_vars *vars, \
struct s_tparser *tparser)
{
	if (tparser_consume_exactly_one_parameter(tparser, TSHELL_STRING))
	{
		ft_ht_print(&vars->environment);
		return (TSHELL_SUCCESS);
	}
	if (ms_vars_export(vars, ft_str_from_cstring(tparser_read(tparser))))
		return (TSHELL_FAILURE);
	return (TSHELL_SUCCESS);
}

t_tshell_status	vars_shell_execute_unset(struct s_ms_vars *vars, \
struct s_tparser *tparser)
{
	if (tparser_consume_exactly_one_parameter(tparser, TSHELL_STRING))
		return (TSHELL_FAILURE);
	ms_vars_unset(vars, ft_str_from_cstring(tparser_read(tparser)));
	return (TSHELL_SUCCESS);
}

t_tshell_status	vars_shell_execute_env(struct s_ms_vars *vars, \
struct s_tparser *tparser)
{
	(void) tparser;
	ft_ht_print(&vars->shell);
	return (TSHELL_SUCCESS);
}

t_tshell_status	vars_shell_print_mannual(void)
{
	printf("%-17s: import contents from environ to both shell and environment database\n", "import");
	printf("%-17s: Add an entry to the shell database\n", "assign var value");
	printf("%-17s: Print the environment database\n", "export");
	printf("%-17s: Copy an entry from the shell database to the environment database\n", "export var");
	printf("%-17s: Add/Update an entry in both shell and environment database\n", "export var value");
	printf("%-17s: Delete an entry in both shell and environment database\n", "unset var");
	printf("%-17s: Print the shell database\n", "env");
	return (TSHELL_SUCCESS);
}

t_tshell_status	vars_shell(struct s_ms_vars *vars, \
struct s_tparser *tparser)
{
	if (!tparser_match_string(tparser, "help"))
	{
		return (vars_shell_print_mannual());
	}
	if (!tparser_match_string(tparser, "import"))
	{
		return (vars_shell_execute_import(vars, tparser));
	}
	if (!tparser_match_string(tparser, "assign"))
	{
		return (vars_shell_execute_assign(vars, tparser));
	}
	if (!tparser_match_string(tparser, "export"))
	{
		return (vars_shell_execute_export(vars, tparser));
	}
	if (!tparser_match_string(tparser, "unset"))
	{
		return (vars_shell_execute_unset(vars, tparser));
	}
	if (!tparser_match_string(tparser, "env"))
	{
		return (vars_shell_execute_env(vars, tparser));
	}
	return (TSHELL_FAILURE);
}

int	main(void)
{
	return (interact(\
		(t_init_func) vars_shell_init, \
		(t_program_func) vars_shell, \
		(t_free_func) ms_vars_free));
}
