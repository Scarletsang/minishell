#ifndef HASHTABLE_TEST_H
# define HASHTABLE_TEST_H

#include "MINISHELL/hashtable.h"

void		expander_hashtable_test1();
void		expander_hashtable_test2();
void		expander_hashtable_test3();

struct s_ht	*hashtable_shell_init(void);
int			hashtable_shell(struct s_ht *ht, const char *line);

#endif