/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:44:42 by htsang            #+#    #+#             */
/*   Updated: 2023/05/18 09:17:19 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void		interact(t_init_func init, t_program_func program, t_free_func cleaner)
{
	struct s_tparser	tparser;
	char				buffer[100];
	void				*states;
	char				*line_end;
	int					program_status;

	states = init();
	if (!states || tparser_create(&tparser, 10))
		return ;
	printf("interactive shell> ");
	fflush(stdout);
	while (read(STDIN_FILENO, buffer, 100) > 0)
	{
		line_end = strrchr(buffer, '\n');
		if (!line_end)
		{
			printf("Line too long\n");
			continue;
		}
		*line_end = 0;
		if(strcmp(buffer, "exit") == 0)
			break;
		tparser_reset(&tparser, buffer);
		program_status = program(states, &tparser);
		if (program_status == -1)
			break;
		if(program_status)
			printf("Program error, received: %s\n", buffer);
		printf("interactive shell> ");
		fflush(stdout);
	}
	cleaner(states);
	tparser_destroy(&tparser);
	free(states);
}
