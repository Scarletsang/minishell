/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:16:51 by sawang            #+#    #+#             */
/*   Updated: 2023/07/07 01:01:27 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_tester.h"

void	print_content_redirection(t_ast_redirection_vector *redirection)
{
	struct s_ft_vector_iterator	vec_itr;

	ft_vector_iterator_init(&vec_itr, (t_ft_vector *)redirection);
	while (!vec_itr.is_end)
	{
		printf("[type:%d ", \
		((struct s_ast_redirection *)ft_vector_iterator_current(&vec_itr))->type);
		printf("content:%s ]", (char *) \
		((struct s_ast_redirection *)ft_vector_iterator_current(&vec_itr))->content.buffer);
		ft_vector_iterator_next(&vec_itr);
	}
}

void	print_content_sb_vector(t_sb_vector *sb_vector)
{
	t_ft_vector_iterator	vec_itr;

	ft_vector_iterator_init(&vec_itr, sb_vector);
	while (!vec_itr.is_end)
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

