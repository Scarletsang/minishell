#ifndef HASHTABLE_TEST_H
# define HASHTABLE_TEST_H

# include "tshell.h"
# include "LIBFT/hashtable.h"

t_ft_ht			*hashtable_shell_init(void);
t_tshell_status	hashtable_shell(t_ft_ht *ht, struct s_tparser *tparser);

#endif