#ifndef VARS_TEST_H
# define VARS_TEST_H

# include "tshell.h"
# include "MINISHELL/execution/vars.h"

struct s_ms_vars	*vars_shell_init(void);

t_tshell_status			vars_shell(struct s_ms_vars *vars, struct s_tparser *tparser);

#endif