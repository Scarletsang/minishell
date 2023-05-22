/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:44:42 by htsang            #+#    #+#             */
/*   Updated: 2023/05/22 21:17:22 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static t_tshell_status	tshell_run(t_program_func program, void *states, \
struct s_tparser *tparser, char *buffer)
{
	t_tshell_status	program_status;

	program_status = program(states, &tparser);
	if (program_status == TSHELL_EXIT)
		return (program_status);
	if(program_status)
		printf("Program error, received: %s\n", buffer);
	return (program_status);
}

void	tshell_lines_init(struct s_tshell_lines *lines)
{
	lines->current_line = lines->buffer;
	lines->current_line_size = 0;
	lines->previous_all_lines_sum_size = 0;
}

static t_tshell_status	tshell_null_terminate_buffer(struct s_tshell_lines *lines)
{
	char	*line_end;

	if (lines->previous_all_lines_sum_size >= TSHELL_MAX_INPUT_SIZE)
		return (TSHELL_FAILURE);
	line_end = strrchr(lines->current_line, '\n');
	if (!line_end)
	{
		printf("Line too long\n");
		return (TSHELL_FAILURE);
	}
	*line_end = 0;
	lines->current_line_size = line_end - lines->current_line;
	lines->previous_all_lines_sum_size += lines->current_line_size;
	return (TSHELL_SUCCESS);
}

void		interact(t_init_func init, t_program_func program, t_free_func cleaner)
{
	struct s_tparser		tparser;
	void					*states;
	struct s_tshell_lines	lines;

	states = init();
	if (!states || tparser_create(&tparser, 10))
		return ;
	printf("interactive shell> ");
	fflush(stdout);
	while ((lines.read_size = read(STDIN_FILENO, lines.buffer, TSHELL_MAX_INPUT_SIZE)) > 0)
	{
		tshell_lines_init(&lines);

		if (tshell_null_terminate_buffer(&lines))
			continue;
		if(strcmp(lines.current_line, "exit") == 0)
			break;
		tparser_reset(&tparser, lines.current_line);
		if (tshell_run(program, states, &tparser, lines.current_line) == TSHELL_EXIT)
			break;
		lines.current_line += lines.current_line_size + 1;
		printf("interactive shell> ");
		fflush(stdout);
	}
	cleaner(states);
	tparser_destroy(&tparser);
	free(states);
}
