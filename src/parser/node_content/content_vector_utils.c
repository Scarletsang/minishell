/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_vector_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:55:28 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 18:31:07 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/content.h"

void	vector_copy_io_redirect(void	*buffer, void *io_redirect)
{
	*(struct s_ast_redirection *)buffer = \
	*(struct s_ast_redirection *)io_redirect;
}

void	vector_copy_sb(void	*buffer, void *sb)
{
	*(t_ft_sb *)buffer = *(t_ft_sb *)sb;
}
