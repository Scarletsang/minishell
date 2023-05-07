/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:19:35 by htsang            #+#    #+#             */
/*   Updated: 2023/05/07 22:04:45 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *line;

	line = readline("minishell>");
    while (line) {
        add_history(line);
        printf("You entered: %s\n", line); // use the line
        rl_replace_line("", 0); // Clear the current input line
        rl_redisplay(); // Update the display of the input line
        free(line); // Free the memory allocated by readline
			line = readline("minishell>");
    }
    return 0;
}
