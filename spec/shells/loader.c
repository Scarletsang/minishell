/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:52:46 by htsang            #+#    #+#             */
/*   Updated: 2023/05/23 18:48:46 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include "tests.h"

static void	*loader_shell_init(void)
{
	return (NULL);
}

static void	loader_something(void *nothing)
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

t_tshell_status	loader_shell_print_mannual(void)
{
	printf("%-23s: List all avaliable shells\n", "list");
	printf("%-23s: Run a shell\n", "run [shell]");
	printf("%-23s: Redirects the content of a file to a shell\n", "run [shell] on [file]");
	return (TSHELL_SUCCESS);
}

static t_tshell_status	loader_shell_execute(void *nothing, struct s_tparser *tparser)
{
	if (tparser_match_string(tparser, "help"))
		return (loader_shell_print_mannual());
}

int	main(void)
{
	interact(loader_shell_init, loader_shell_execute, NULL);
	return (0);
}
