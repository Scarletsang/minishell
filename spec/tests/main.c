/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:52:46 by htsang            #+#    #+#             */
/*   Updated: 2023/05/18 00:22:06 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "hashtable_test.h"

int	main(void)
{
	// expander_hashtable_test1();
	// expander_hashtable_test3();
	interact(\
		(t_init_func) hashtable_shell_init, \
		(t_program_func) hashtable_shell, \
		(t_free_func) ht_destroy);
	return (0);
}