/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:27:10 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/26 13:36:40 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

# include <stdlib.h>
# include "libft.h"
# include "MINISHELL/vector.h"
# include "MINISHELL/hashtable.h"
# include "MINISHELL/stringbuilder.h"

struct s_minishell_vars
{
	t_ht		environment;
	t_ht		shell;
	t_vector	envp;
	bool		environnement_changed;
};

int		minishell_vars_init(struct s_minishell_vars *vars);

void	minishell_vars_free(struct s_minishell_vars *vars);

int		minishell_vars_import(struct s_minishell_vars *vars, char **envp);

////////////////////////////////////////////
////////////     getters     ///////////////
////////////////////////////////////////////

char	**minishell_vars_get_envp(struct s_minishell_vars *vars);

char	*minishell_vars_extract_key(const t_sb *key_and_value);

int		minishell_vars_database_set(t_ht *database, const t_sb *key_and_value);

char	*minishell_vars_database_get(t_ht *database, const t_sb *key_and_value);

////////////////////////////////////////////
////////////     actions     ///////////////
////////////////////////////////////////////

int		minishell_vars_export(struct s_minishell_vars *vars, \
const t_sb *value_and_name);

void	minishell_vars_unset(struct s_minishell_vars *vars, \
const t_sb *value_and_name);

char	*minishell_vars_echo(struct s_minishell_vars *vars, \
const t_sb *value_and_name);

#endif