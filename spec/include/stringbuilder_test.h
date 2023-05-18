#ifndef STRINGBUILDER_TEST_H
# define STRINGBUILDER_TEST_H

# include "tests.h"
# include "MINISHELL/stringbuilder.h"

struct s_sb		*stringbuilder_shell_init(void);

t_tshell_status	stringbuilder_shell(struct s_sb *sb, struct s_tparser *tparser);

#endif