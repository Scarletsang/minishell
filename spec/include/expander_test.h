#ifndef EXPANDER_TEST_H
# define EXPANDER_TEST_H

# include "tshell.h"
# include "MINISHELL/execution/expander.h"


struct s_ms_vars	*expander_shell_init(void);

t_tshell_status			expander_shell(struct s_ms_vars *vars, struct s_tparser *tparser);

#endif