#ifndef HASHTABLE_TEST_H
# define HASHTABLE_TEST_H

# include "tests.h"
# include "MINISHELL/hashtable.h"

void		expander_hashtable_test1();
void		expander_hashtable_test2();
void		expander_hashtable_test3();

t_ht			*hashtable_shell_init(void);
t_tshell_status	hashtable_shell(t_ht *ht, struct s_tparser *tparser);

#endif