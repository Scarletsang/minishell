/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:16:51 by sawang            #+#    #+#             */
/*   Updated: 2023/06/14 15:08:11 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
// #include <stdio.h>
// #include "MINISHELL/lexer/lexer.h"
#include "MINISHELL/parser/parser.h"
#include <readline/readline.h>
#include <readline/history.h>

void	print_content_redirection(struct s_ast_redirection_vector *redirection)
{
	struct s_vector_iterator	*vec_itr;

	vector_iterator_init(vec_itr, (t_vector *)redirection);
	while (!vector_iterator_end(vec_itr))
	{
		printf("type:%d ", \
		((struct s_ast_redirection *)vector_iterator_current(vec_itr))->type);
		printf("content:%s ", \
		((struct s_ast_redirection *)vector_iterator_current(vec_itr))->content);
		vector_iterator_next(vec_itr);
	}
}

void	print_content_sb_vector(t_sb_vector *sb_vector)
{
	struct s_vector_iterator	*vec_itr;

	vector_iterator_init(vec_itr, (t_vector *)sb_vector);
	while (!vector_iterator_end(vec_itr))
	{
		printf("%s ", (char *)vector_iterator_current(vec_itr));
		vector_iterator_next(vec_itr);
	}
}

void	print_ast_content(struct s_ast_node_content *content)
{
	if (content == NULL)
		return ;
	printf("redirection_in: ");
	print_content_redirection(&content->redirection_in);
	printf("\tredirection_out: ");
	print_content_redirection(&content->redirection_out);
	printf("\tassignment_word: ");
	print_content_sb_vector(&content->assignment_word);
	printf("\tcommand: ");
	print_content_sb_vector(&content->command);
}

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
				// print malloc fail
				// free ast
			else if (parser_exit_code == PARSER_FAILURE)
				// print syntex error
				// and free ast
			else
				print_ast(parser.head);
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
