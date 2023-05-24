/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:44:42 by htsang            #+#    #+#             */
/*   Updated: 2023/05/24 12:43:09 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tshell.h"

static t_tshell_status	tshell_interpret(t_program_func program, \
void *states, struct s_tshell *tshell)
{
	t_tshell_status	line_process_status;
	t_tshell_status	program_status;

	line_process_status = tshell_lines_process_one(&tshell->lines);
	if (line_process_status == TSHELL_EXIT)
	{
		printf("Line too long\n");
		return (TSHELL_EXIT);
	}
	while (!line_process_status)
	{
		program_status = tshell_builtins_exit(&tshell->lines);
		if (program_status == TSHELL_FAILURE)
		{
			tparser_reset(&tshell->tparser, tshell->lines.current_line);
			program_status = tshell_builtins_load(program, states, tshell);
		}
		if (program_status == TSHELL_FAILURE)
		{
			tparser_reset(&tshell->tparser, tshell->lines.current_line);
			program_status = program(states, &tshell->tparser);
		}
		if (program_status == TSHELL_EXIT)
			return (TSHELL_EXIT);
		if (program_status == TSHELL_FAILURE)
			printf("Program error, received: %s\n", tshell->lines.current_line);
		tshell->lines.current_line += tshell->lines.current_line_size + 1;
		line_process_status = tshell_lines_process_one(&tshell->lines);
	}
	return (TSHELL_SUCCESS);
}

t_tshell_status	tshell_run(t_program_func program, void *states)
{
	struct s_tshell	tshell;

	if (tparser_create(&tshell.tparser, 10) || tshell_lines_init(&tshell.lines))
		return (TSHELL_EXIT);
	printf("interactive shell> ");
	fflush(stdout);
	while ((tshell.lines.read_size = read(STDIN_FILENO, tshell.lines.buffer, TSHELL_MAX_INPUT_SIZE)) > 0)
	{
		tshell.lines.buffer[tshell.lines.read_size] = 0;
		if (tshell_interpret(program, states, &tshell) == TSHELL_EXIT)
			break ;
		tshell_lines_reset(&tshell.lines);
		printf("interactive shell> ");
		fflush(stdout);
	}
	tshell_lines_free(&tshell.lines);
	tparser_destroy(&tshell.tparser);
	return (TSHELL_SUCCESS);
}

t_tshell_status	tshell_run_from_fd(t_program_func program, void *states, int fd)
{
	struct s_tshell	tshell;

	if (tparser_create(&tshell.tparser, 10) || tshell_lines_init(&tshell.lines))
		return (TSHELL_EXIT);
	while ((tshell.lines.read_size = read(fd, tshell.lines.buffer, TSHELL_MAX_INPUT_SIZE)) > 0)
	{
		tshell.lines.buffer[tshell.lines.read_size] = 0;
		if (tshell_interpret(program, states, &tshell) == TSHELL_EXIT)
			break ;
		tshell_lines_reset(&tshell.lines);
	}
	tshell_lines_free(&tshell.lines);
	tparser_destroy(&tshell.tparser);
	return (TSHELL_SUCCESS);
}

void	interact(t_init_func init, t_program_func program, t_free_func cleaner)
{
	void	*states;

	states = init();
	if (!states)
		return ;
	tshell_run(program, states);
	if (states)
	{
		if (cleaner)
			cleaner(states);
		free(states);
	}
}
