/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:47:51 by sawang            #+#    #+#             */
/*   Updated: 2023/07/07 01:00:40 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/parser/content.h"

int	ast_redirect_type_set(t_token_type token_type, \
	t_ast_redirection_type *io_file_type)
{
	if (token_type == TOKEN_LESS)
		*io_file_type = REDIRCT_STDIN;
	else if (token_type == TOKEN_DLESS)
		*io_file_type = REDIRECT_HEREDOC;
	else if (token_type == TOKEN_GREAT)
		*io_file_type = REDIRECT_STDOUT;
	else if (token_type == TOKEN_DGREAT)
		*io_file_type = REDIRECT_STDOUT_APPEND;
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ast_node_str_set(t_ft_sb *content_str, const char *str, \
const size_t str_len)
{
	if ((ft_sb_init(content_str, 10) == EXIT_FAILURE) || \
		(ft_sb_perform(content_str, \
			ft_sb_action_append(ft_str_slice(str, 0, str_len))) \
			== EXIT_FAILURE))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
