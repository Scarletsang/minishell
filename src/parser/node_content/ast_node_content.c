/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:36:57 by sawang            #+#    #+#             */
/*   Updated: 2023/06/19 18:31:55 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/parser/content.h"

int	ast_node_content_init(\
	struct s_ast_node_content *node_cmd_content)
{
	if (ft_vector_init(&node_cmd_content->redirection_in, \
			sizeof(struct s_ast_redirection), 5, vector_copy_io_redirect) || \
			ft_vector_init(&node_cmd_content->redirection_out, \
			sizeof(struct s_ast_redirection), 5, vector_copy_io_redirect) || \
			ft_vector_init(&node_cmd_content->assignment, \
			sizeof(t_ft_sb), 5, vector_copy_sb) || \
			ft_vector_init(&node_cmd_content->command, \
			sizeof(t_ft_sb), 5, vector_copy_sb))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ast_node_content_free(struct s_ast_node_content *content)
{
	if (content->redirection_in.buffer)
		free_io_redirect_vector(&content->redirection_in);
	if (content->redirection_out.buffer)
		free_io_redirect_vector(&content->redirection_out);
	if (content->assignment.buffer)
		free_sb_vector(&content->assignment);
	if (content->command.buffer)
		free_sb_vector(&content->command);
	free(content);
}
