/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:44:42 by htsang            #+#    #+#             */
/*   Updated: 2023/05/13 14:58:23 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void		interact(t_init_func init, t_program_func program, t_free_func cleaner)
{
	char	buffer[100];
	char	*line_end;
	void	*states;
	int		program_status;

	states = init();
	if (!states)
		return ;
	printf("interact shell> ");
	fflush(stdout);
	while (read(STDIN_FILENO, buffer, 100) != -1)
	{
		line_end = ft_strrchr(buffer, '\n');
		if (!line_end)
		{
			printf("Line too long\n");
			continue;
		}
		*line_end = 0;
		if(ft_strcmp(buffer, "exit") == 0)
			break;
		program_status = program(states, buffer);
		if (program_status == -1)
			break;
		if(program_status)
			printf("Program error, received: %s\n", buffer);
		printf("interact shell> ");
		fflush(stdout);
	}
	cleaner(states);
	free(states);
}
