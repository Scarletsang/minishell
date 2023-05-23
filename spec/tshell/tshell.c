/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tshell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 05:58:21 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/23 20:57:35 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

///////////////////////////////////////////
/////////////     lines     ///////////////
///////////////////////////////////////////

void	tshell_lines_init(struct s_tshell_lines *lines)
{
	lines->current_line = lines->buffer;
	lines->current_line_size = 0;
	lines->previous_all_lines_sum_size = 0;
}

t_tshell_status	tshell_lines_process_one(struct s_tshell_lines *lines)
{
	char	*line_end;

	if (lines->previous_all_lines_sum_size >= TSHELL_MAX_INPUT_SIZE)
		return (TSHELL_FAILURE);
	line_end = strchr(lines->current_line, '\n');
	if (!line_end)
		return (TSHELL_EXIT);
	*line_end = 0;
	lines->current_line_size = line_end - lines->current_line;
	lines->previous_all_lines_sum_size += lines->current_line_size;
	return (TSHELL_SUCCESS);
}

//////////////////////////////////////////////
/////////////     builtins     ///////////////
//////////////////////////////////////////////

t_tshell_status	tshell_builtins_exit(struct s_tshell_lines *lines)
{
	if (strcmp(lines->current_line, "exit") == 0)
		return (TSHELL_EXIT);
	return (TSHELL_SUCCESS);
}

t_tshell_status	tshell_builtins_load(void *states, struct s_tparser *tparser)
{
	if (tparser_match_string(tparser, "load"))
	{
		tparser_ignore_spaces(tparser);
		if (tparser_consume_exactly_one_parameter(tparser, TSHELL_STRING))
			return (TSHELL_FAILURE);
		if (tparser_match_char(tparser, '\0'))
			return (TSHELL_FAILURE);
		
		return (TSHELL_SUCCESS);
	}
	return (TSHELL_FAILURE);
}

//////////////////////////////////////////////
/////////////     execution     //////////////
//////////////////////////////////////////////

t_tshell_status	tshell_execute_printer(void *states, \
struct s_tparser *tparser, t_printer_func func)
{
	tparser_ignore_spaces(tparser);
	if (tparser_match_char(tparser, '\0'))
		return (TSHELL_FAILURE);
	func(states);
	return (TSHELL_SUCCESS);
}
