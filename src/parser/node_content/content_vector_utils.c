/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_vector_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:55:28 by sawang            #+#    #+#             */
/*   Updated: 2023/06/16 20:55:52 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/content.h"

void	vector_set_io_redirect(void	*buffer, void *io_redirect)
{
	*(struct s_ast_redirection *)buffer = \
	*(struct s_ast_redirection *)io_redirect;
}

void	vector_set_sb(void	*buffer, void *sb)
{
	*(t_sb *)buffer = *(t_sb *)sb;
}
