/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:36:57 by sawang            #+#    #+#             */
/*   Updated: 2023/06/16 20:58:37 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/parser/content.h"

int	ast_node_content_init(\
	struct s_ast_node_content *node_cmd_content)
{
	if (vector_init(&node_cmd_content->redirection_in, \
			sizeof(struct s_ast_redirection), 5, vector_set_io_redirect) || \
			vector_init(&node_cmd_content->redirection_out, \
			sizeof(struct s_ast_redirection), 5, vector_set_io_redirect) || \
			vector_init(&node_cmd_content->assignment_word, \
			sizeof(t_sb), 5, vector_set_sb) || \
			vector_init(&node_cmd_content->command, \
			sizeof(t_sb), 5, vector_set_sb))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ast_node_content_free(struct s_ast_node_content *content)
{
	if (content->redirection_in.buffer)
		free_io_redirect_vector(&content->redirection_in);
	if (content->redirection_out.buffer)
		free_io_redirect_vector(&content->redirection_out);
	if (content->assignment_word.buffer)
		free_sb_vector(&content->assignment_word);
	if (content->command.buffer)
		free_sb_vector(&content->command);
	free(content);
}
