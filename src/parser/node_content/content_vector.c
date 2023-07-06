/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:57:07 by sawang            #+#    #+#             */
/*   Updated: 2023/07/07 01:06:50 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/content.h"

void	free_io_redirect_vector(\
	t_ast_redirection_vector *io_redirect_vector)
{
	struct s_ft_vector_iterator	vec_itr;

	ft_vector_iterator_init(&vec_itr, (t_ft_vector *)io_redirect_vector);
	while (!vec_itr.is_end)
	{
		ft_sb_free(\
			&((struct s_ast_redirection *)ft_vector_iterator_current(\
			&vec_itr))->content);
		ft_vector_iterator_next(&vec_itr);
	}
	ft_vector_free((t_ft_vector *)io_redirect_vector);
}

void	free_sb_vector(t_sb_vector *sb_vector)
{
	struct s_ft_vector_iterator	vec_itr;

	ft_vector_iterator_init(&vec_itr, (t_ft_vector *)sb_vector);
	while (!vec_itr.is_end)
	{
		ft_sb_free((t_ft_sb *)ft_vector_iterator_current(&vec_itr));
		ft_vector_iterator_next(&vec_itr);
	}
	ft_vector_free((t_ft_vector *)sb_vector);
}
