/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:52:46 by htsang            #+#    #+#             */
/*   Updated: 2023/05/22 12:42:56 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "hashtable_test.h"
#include "stringbuilder_test.h"

int	main(void)
{
	// expander_hashtable_test1();
	// expander_hashtable_test3();
	interact(\
		(t_init_func) hashtable_shell_init, \
		(t_program_func) hashtable_shell, \
		(t_free_func) ht_free);
	// interact(\
	// 	(t_init_func) stringbuilder_shell_init, \
	// 	(t_program_func) stringbuilder_shell, \
	// 	(t_free_func) sb_free);
	return (0);
}
