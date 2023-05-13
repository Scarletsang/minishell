#ifndef TESTS_H
# define TESTS_H

#include "MINISHELL/expander/hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef	void	*(*t_init_func)(void);
typedef	int		(*t_program_func)(void *states, const char *line);
typedef	void	(*t_free_func)(void *states);

void		expander_hashtable_test1();
void		expander_hashtable_test2();
void		expander_hashtable_test3();

struct s_ht	*hashtable_shell_init(void);
int			hashtable_shell(struct s_ht *ht, const char *line);
void		interact(t_init_func init, t_program_func program, t_free_func cleaner);

#endif