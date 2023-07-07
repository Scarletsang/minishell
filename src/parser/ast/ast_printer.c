/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:16:51 by sawang            #+#    #+#             */
/*   Updated: 2023/07/07 11:09:06 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "MINISHELL/parser/ast.h"

void	ast_redirection_vector_print(t_ast_redirection_vector *redirection)
{
	struct s_ft_vector_iterator	vec_itr;

	ft_vector_iterator_begin(&vec_itr, (t_ft_vector *)redirection);
	while (!vec_itr.is_end)
	{
		printf("[type:%d ", ((struct s_ast_redirection *) \
			ft_vector_iterator_current(&vec_itr))->type);
		printf("content:%s ]", (char *)((struct s_ast_redirection *) \
			ft_vector_iterator_current(&vec_itr))->content.buffer);
		ft_vector_iterator_next(&vec_itr);
	}
}

void	sb_vector_print(t_sb_vector *sb_vector)
{
	t_ft_vector_iterator	vec_itr;

	ft_vector_iterator_begin(&vec_itr, sb_vector);
	while (!vec_itr.is_end)
	{
		printf("[%s] ", (char *)((t_ft_sb *) \
			ft_vector_iterator_current(&vec_itr))->buffer);
		ft_vector_iterator_next(&vec_itr);
	}
}

void	ast_node_content_print(struct s_ast_node_content *content)
{
	if (content == NULL)
		return ;
	printf("redirection_in: ");
	ast_redirection_vector_print(&content->redirection_in);
	printf("\tredirection_out: ");
	ast_redirection_vector_print(&content->redirection_out);
	printf("\tassignment_word: ");
	sb_vector_print(&content->assignment);
	printf("\tcommand: ");
	sb_vector_print(&content->command);
}
