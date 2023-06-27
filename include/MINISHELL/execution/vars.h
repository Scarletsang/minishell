/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:27:10 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/26 04:50:24 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

# include <stdlib.h>
# include "LIBFT/hashtable.h"

////////////////////////////////////////////////////////////
////////////    minishell vars interface    ////////////////
////////////////////////////////////////////////////////////

/**
 * @brief Holds all the variables of the minishell. There are 3 databases that
 * are used to store the variables: environment, special and shell.
 * 
 * @param environment This database stores variables that will be exported to
 * the child processes.
 * @param special This database stores variables that are special to the
 * minishell, such as the last return code.
 * @param shell This database stores variables that are only used by the
 * minishell, such as the current working directory.
 * @param envp This vector stores the environment variables in the format that
 * is expected by the execve() function.
 * @param environnement_changed This boolean is set to true when the environment
 * variables are changed. It is an indicator of whether or not the envp vector
 * needs to be updated.
 * 
*/
struct s_ms_vars
{
	t_ft_ht		environment;
	t_ft_ht		special;
	t_ft_ht		shell;
	bool		environnement_changed;
};

int			ms_vars_init(struct s_ms_vars *vars);

void		ms_vars_free(struct s_ms_vars *vars);

/**
 * @brief Import all the environment variables from the given envp, usually from
 * the extern environ variable, into the environment database. Since the expected
 * envp is managed by the operating system, they are not store as copy, but as
 * reference. The imported values are not owned by the database and therefore
 * will not be freed when the database is freed.
*/
int			ms_vars_import(struct s_ms_vars *vars, char **envp);

int			ms_vars_import_default_special(struct s_ms_vars *vars);

/**
 * @brief Add an entry to the given database. If the entry already exists, it
 * will be updated. The value is copied and therefore it is owned by the
 * database, meaning that it will be freed when the database is freed.
*/
int			ms_vars_database_set(t_ft_ht *database, const char *key, \
const char *value);

const char	*ms_vars_database_get(const t_ft_ht *database, const char *key);

/////////////////////////////////////////////////////////////////////////
////////////     interface used by minishell builtins     ///////////////
/////////////////////////////////////////////////////////////////////////

/**
 * @brief Add an entry to the shell database. If the entry already exists,
 * it will be updated. The entry is owned by the database, meaning that it will
 * be freed when the database is freed.
*/
int			ms_vars_declare(struct s_ms_vars *vars, \
const char *key, const char *value);

/**
 * @brief Copy an entry from the shell database to the environment database.
 * The entry stored in the envionment database is not owned by the environment
 * database.
*/
int			ms_vars_export(struct s_ms_vars *vars, \
const char *key);

/**
 * @brief Remove an entry from both the shell and environment databases.
*/
void		ms_vars_unset(struct s_ms_vars *vars, \
const char *key);

/**
 * @brief Query the shell database for the given key. If the key is not found,
 * the environment database is also queried.
*/
const char	*ms_vars_echo(const struct s_ms_vars *vars, \
const char *key);

#endif