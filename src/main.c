/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:20:29 by htsang            #+#    #+#             */
/*   Updated: 2023/06/01 15:24:12 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*line;

	line = readline("minishell>");
	while (line) {
		// TODO: Parsing + lexing
		// TODO: expander + execution here
		printf("You entered: %s\n", line);
		add_history(line);
		 // Clear the current input line
		rl_replace_line("", 0);
		// Update the display of the input line
		rl_redisplay();
		// Free the memory allocated by readline
		free(line);
		line = readline("minishell>");
	}
	return 0;
}
