/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:52:46 by htsang            #+#    #+#             */
/*   Updated: 2023/05/23 12:42:50 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include "tests.h"

static void	*shell_shell_init(void)
{
	return (NULL);
}

static t_tshell_status	shell_shell_execute(void *nothing, struct s_tparser *tparser)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (tparser_consume_exactly_one_parameter(tparser, TSHELL_STRING))
			return (TSHELL_FAILURE);
		execlp(tparser_read(tparser), tparser_read(tparser), NULL);
		return (TSHELL_FAILURE);
	}
	waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	interact(shell_shell_init, shell_shell_execute, NULL);
	return (0);
}
