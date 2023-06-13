/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:16:51 by sawang            #+#    #+#             */
/*   Updated: 2023/06/13 15:21:27 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
// #include <stdio.h>
// #include "MINISHELL/lexer/lexer.h"
#include "MINISHELL/parser/parser.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char				*line;
	struct s_lexer		lexer;
	t_lexer_exit_code	lexer_exit_code;
	struct s_parser		parser;
	t_parser_exit_code	parser_exit_code;

	line = readline("minishell>");
	while (line)
	{
		add_history(line);
		lexer_init(&lexer);
		lexer_exit_code = token_list_get(&lexer, line);
		// token_lstitr_print(lexer.start, (t_token_printer)token_print);
		if (parser_check_before_run(lexer, lexer_exit_code) == EXIT_SUCCESS)
		{
			parser_init(parser, lexer.start);
			parser_exit_code = parse_complete_command(&parser);
			if (parser.malloc_fail == true)
				// free ast
			else if (parser_exit_code == PARSER_SUCCESS)
				// print ast
			else
				// print syntex error
			// free lexer
		}
		else
			return (EXIT_FAILURE);
		rl_replace_line("", 0); // Clear the current input line
        rl_redisplay(); // Update the display of the input line
        free(line); // Free the memory allocated by readline
		line = readline("minishell>");
	}
	return (parser_exit_code);
}
