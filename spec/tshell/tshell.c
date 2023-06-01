/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tshell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 05:58:21 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/06/01 15:25:13 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tshell.h"
#include <fcntl.h>

///////////////////////////////////////////
/////////////     lines     ///////////////
///////////////////////////////////////////

t_tshell_status	tshell_lines_init(struct s_tshell_lines *lines)
{
	lines->buffer = calloc(TSHELL_MAX_INPUT_SIZE, sizeof(char));
	if (!lines->buffer)
		return (TSHELL_FAILURE);
	tshell_lines_reset(lines);
	return (TSHELL_SUCCESS);
}

void	tshell_lines_reset(struct s_tshell_lines *lines)
{
	lines->current_line = lines->buffer;
	lines->current_line_size = 0;
	lines->previous_all_lines_sum_size = 0;
}

void	tshell_lines_free(struct s_tshell_lines *lines)
{
	free(lines->buffer);
}

t_tshell_status	tshell_lines_process_one(struct s_tshell_lines *lines)
{
	if (lines->previous_all_lines_sum_size >= ((size_t) lines->read_size - 1))
		return (TSHELL_FAILURE);
	lines->current_line_size = 0;
	while (lines->previous_all_lines_sum_size < (size_t) lines->read_size)
	{
		lines->current_line_size++;
		lines->previous_all_lines_sum_size++;
		if (lines->current_line[lines->current_line_size] == '\n')
			break ;
	}
	lines->current_line[lines->current_line_size] = '\0';
	return (TSHELL_SUCCESS);
}

//////////////////////////////////////////////
/////////////     builtins     ///////////////
//////////////////////////////////////////////

t_tshell_status	tshell_builtins_exit(struct s_tshell_lines *lines)
{
	if (strcmp(lines->current_line, "exit") == 0)
		return (TSHELL_EXIT);
	return (TSHELL_FAILURE);
}

t_tshell_status	tshell_builtins_load(t_program_func program, \
void *states, struct s_tshell *tshell)
{
	int		file;
	char	*filename;

	if (!tparser_match_string(&tshell->tparser, "load"))
	{
		tparser_ignore_spaces(&tshell->tparser);
		if (tparser_consume_exactly_one_parameter(&tshell->tparser, TSHELL_STRING))
			return (TSHELL_FAILURE);
		if (tparser_match_char(&tshell->tparser, '\0'))
			return (TSHELL_FAILURE);
		filename = (char *) tparser_read(&tshell->tparser);
		file = open(filename, O_RDONLY);
		if (file == -1)
		{
			printf("File %s not found\n", filename);
			return (TSHELL_FAILURE);
		}
		tshell_run_from_fd(program, states, file);
		close(file);
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
