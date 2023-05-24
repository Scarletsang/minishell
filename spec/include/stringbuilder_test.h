#ifndef STRINGBUILDER_TEST_H
# define STRINGBUILDER_TEST_H

# include "tshell.h"
# include "MINISHELL/stringbuilder.h"

t_sb			*stringbuilder_shell_init(void);

t_tshell_status	stringbuilder_shell(t_sb *sb, struct s_tparser *tparser);

#endif