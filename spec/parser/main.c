/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 01:16:34 by htsang            #+#    #+#             */
/*   Updated: 2023/06/24 01:18:47 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "parser_tester.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char				*line;
	struct s_ast_node	*ast_root;
	t_ms_status			prog_stats;

	line = readline("minishell>");
	while (line)
	{
		ast_root = NULL;
		prog_stats = parser_run(&ast_root, line);
		printf("prog_stats: %d\n", prog_stats);
		if (prog_stats == PROGRAM_SUCCESS)
			print_ast(ast_root);
		ast_node_free(ast_root);
		// rl_replace_line("", 0); // Clear the current input line
        // rl_redisplay(); // Update the display of the input line
        free(line); // Free the memory allocated by readline
		line = readline("minishell>");
	}
	return (EXIT_SUCCESS);
}