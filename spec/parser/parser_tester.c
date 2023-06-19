/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:16:51 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 19:24:48 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
// #include <stdio.h>
#include "MINISHELL/parser.h"
#include <readline/readline.h>
#include <readline/history.h>

void	print_ast(struct s_ast_node *root);

static void	print_content_redirection(t_ast_redirection_vector *redirection)
{
	struct s_ft_vector_iterator	vec_itr;

	ft_vector_iterator_init(&vec_itr, (t_ft_vector *)redirection);
	while (!ft_vector_iterator_is_end(&vec_itr))
	{
		printf("[type:%d ", \
		((struct s_ast_redirection *)ft_vector_iterator_current(&vec_itr))->type);
		printf("content:%s ]", \
		((struct s_ast_redirection *)ft_vector_iterator_current(&vec_itr))->content.buffer);
		ft_vector_iterator_next(&vec_itr);
	}
}

static void	print_content_sb_vector(t_sb_vector *sb_vector)
{
	t_ft_vector_iterator	vec_itr;

	ft_vector_iterator_init(&vec_itr, sb_vector);
	while (!ft_vector_iterator_is_end(&vec_itr))
	{
		printf("[%s] ", (char *) ((t_ft_sb *)ft_vector_iterator_current(&vec_itr))->buffer);
		ft_vector_iterator_next(&vec_itr);
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
	print_content_sb_vector(&content->assignment);
	printf("\tcommand: ");
	print_content_sb_vector(&content->command);
}

int	main(void)
{
	char				*line;
	struct s_ast_node	*ast_root;

	line = readline("minishell>");
	while (line)
	{
		ast_root = parser_run(line);
		if (ast_root)
			print_ast(ast_root);
		ast_node_free(ast_root);
		// rl_replace_line("", 0); // Clear the current input line
        // rl_redisplay(); // Update the display of the input line
        free(line); // Free the memory allocated by readline
		line = readline("minishell>");
	}
	return (EXIT_SUCCESS);
}
