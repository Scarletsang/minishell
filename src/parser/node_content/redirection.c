/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:47:51 by sawang            #+#    #+#             */
/*   Updated: 2023/06/16 21:11:14 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ast_node_str_set(t_sb *content_str, const char *str, \
const size_t str_len)
{
	if ((sb_init(content_str, 10) == EXIT_FAILURE) || \
		(sb_perform(content_str, \
			sb_action_append_len(str, str_len)) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
