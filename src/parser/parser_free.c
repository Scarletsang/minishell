/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:16:23 by sawang            #+#    #+#             */
/*   Updated: 2023/06/16 16:03:33 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/parser.h"

void	free_io_redirect_vector(t_ast_redirection_vector *io_redirect_vector)
{
	struct s_vector_iterator	*vec_itr;

	vector_iterator_init(vec_itr, (t_vector *)io_redirect_vector);
	while (!vector_iterator_end(vec_itr))
	{
		sb_free(\
			&((struct s_ast_redirection *)vector_iterator_current(\
			vec_itr))->content);
		vector_iterator_next(vec_itr);
	}
	vector_free((t_vector *)io_redirect_vector);

}

void	free_sb_vector(t_sb_vector *sb_vector)
{
	struct s_vector_iterator	*vec_itr;

	vector_iterator_init(vec_itr, (t_vector *)sb_vector);
	while (!vector_iterator_end(vec_itr))
	{
		sb_free((t_sb *)vector_iterator_current(vec_itr));
		vector_iterator_next(vec_itr);
	}
	vector_free((t_vector *)sb_vector);
}

void	free_node_content(struct s_ast_node_content *content)
{
	if (&content->redirection_in)
		free_io_redirect_vector(&content->redirection_in);
	if (&content->redirection_out)
		free_io_redirect_vector(&content->redirection_out);
	if (&content->assignment_word)
		free_sb_vector(&content->assignment_word);
	if (&content->command)
		free_sb_vector(&content->command);
	free(content);
}

void	free_node(struct s_ast_node *node)
{
	if (node == NULL)
		return ;
	free_node(node->left);
	free_node(node->right);
	if (node->content)
	{
		free_node_content(node->content);
		free(node);
	}
	else
		free(node);
}
