#ifndef STRINGBUILDER_TEST_H
# define STRINGBUILDER_TEST_H

#include "MINISHELL/stringbuilder.h"

struct s_sb	*stringbuilder_shell_init(void);
int			stringbuilder_shell(struct s_sb *sb, const char *line);

#endif