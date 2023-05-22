/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:27:10 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/22 15:09:46 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

# include <stdlib.h>
# include "libft.h"
# include "MINISHELL/vector.h"
# include "MINISHELL/hashtable.h"
# include "MINISHELL/stringbuilder.h"

struct s_minishell_environ
{
	char			**buffer;
	unsigned int	last_environment_size;
	bool			environment_changed;
};

struct s_minishell_vars
{
	t_ht						*environment;
	t_ht						*shell;
	struct s_minishell_environ	environ;
};

int		minishell_vars_init(struct s_minishell_vars *vars);

void	minishell_vars_destroy(struct s_minishell_vars *vars);

int		minishell_vars_import(struct s_minishell_vars *vars, char **envp);

int		minishell_vars_export_environ(struct s_minishell_vars *vars);

////////////////////////////////////////////
////////////     getters     ///////////////
////////////////////////////////////////////

int		minishell_vars_set_shell(struct s_minishell_vars *vars, char *name, \
char *value);

int		minishell_vars_set_environmental(struct s_minishell_vars *vars, \
char *name, char *value);

////////////////////////////////////////////
////////////     actions     ///////////////
////////////////////////////////////////////

int		minishell_vars_export(struct s_minishell_vars *vars, char *name);

int		minishell_vars_unset(struct s_minishell_vars *vars, char *name);

char	*minishell_vars_echo(struct s_minishell_vars *vars, char *name);

#endif