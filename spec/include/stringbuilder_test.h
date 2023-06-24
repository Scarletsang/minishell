#ifndef STRINGBUILDER_TEST_H
# define STRINGBUILDER_TEST_H

# include "tshell.h"
# include "LIBFT/stringbuilder.h"

t_ft_sb			*stringbuilder_shell_init(void);

t_tshell_status	stringbuilder_shell(t_ft_sb *sb, struct s_tparser *tparser);

#endif