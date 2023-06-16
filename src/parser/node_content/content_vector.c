/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:57:07 by sawang            #+#    #+#             */
/*   Updated: 2023/06/16 20:58:27 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/content.h"

void	free_io_redirect_vector(\
	t_ast_redirection_vector *io_redirect_vector)
{
	struct s_vector_iterator	vec_itr;

	vector_iterator_init(&vec_itr, (t_vector *)io_redirect_vector);
	while (!vector_iterator_is_end(&vec_itr))
	{
		sb_free(\
			&((struct s_ast_redirection *)vector_iterator_current(\
			&vec_itr))->content);
		vector_iterator_next(&vec_itr);
	}
	vector_free((t_vector *)io_redirect_vector);
}

void	free_sb_vector(t_sb_vector *sb_vector)
{
	struct s_vector_iterator	vec_itr;

	vector_iterator_init(&vec_itr, (t_vector *)sb_vector);
	while (!vector_iterator_is_end(&vec_itr))
	{
		sb_free((t_sb *)vector_iterator_current(&vec_itr));
		vector_iterator_next(&vec_itr);
	}
	vector_free((t_vector *)sb_vector);
}
