/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tshell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 05:58:21 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/18 07:48:12 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

t_tshell_status	tshell_execute_printer(void *states, \
struct s_tparser *tparser, t_printer_func func)
{
	tparser_ignore_spaces(tparser);
	if (tparser_match_char(tparser, '\0'))
		return (TSHELL_FAILURE);
	func(states);
	return (TSHELL_SUCCESS);
}
