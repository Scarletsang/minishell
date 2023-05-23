/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:44:42 by htsang            #+#    #+#             */
/*   Updated: 2023/05/23 21:01:50 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static t_tshell_status	tshell_run(t_program_func program, void *states, \
struct s_tparser *tparser, struct s_tshell_lines *lines)
{
	t_tshell_status	line_process_status;
	t_tshell_status	program_status;

	line_process_status = tshell_lines_process_one(lines);
	if (line_process_status == TSHELL_EXIT)
	{
		printf("Line too long\n");
		return (TSHELL_EXIT);
	}
	while (!line_process_status)
	{
		program_status = tshell_builtins_exit(lines);
		if (program_status == TSHELL_FAILURE)
		{
			program_status = tshell_builtins_load(states, tparser);
			tparser_reset(tparser, lines->current_line);
		}
		if (program_status == TSHELL_FAILURE)
		{
			program_status = program(states, tparser);
			tparser_reset(tparser, lines->current_line);
		}
		if (program_status == TSHELL_EXIT)
			return (TSHELL_EXIT);
		if (program_status == TSHELL_FAILURE)
			printf("Program error, received: %s\n", lines->current_line);
		lines->current_line += lines->current_line_size + 1;
		line_process_status = tshell_lines_process_one(lines);
	}
	return (TSHELL_SUCCESS);
}

void		interact(t_init_func init, t_program_func program, t_free_func cleaner)
{
	void					*states;
	struct s_tparser		tparser;
	struct s_tshell_lines	lines;

	states = init();
	if (!states || tparser_create(&tparser, 10))
		return ;
	printf("interactive shell> ");
	fflush(stdout);
	while ((lines.read_size = read(STDIN_FILENO, lines.buffer, TSHELL_MAX_INPUT_SIZE)) > 0)
	{
		tshell_lines_init(&lines);
		if (tshell_run(program, states, &tparser, &lines) == TSHELL_EXIT)
			break ;
		printf("interactive shell> ");
		fflush(stdout);
	}
	tparser_destroy(&tparser);
	if (states)
	{
		if (cleaner)
			cleaner(states);
		free(states);
	}
}
