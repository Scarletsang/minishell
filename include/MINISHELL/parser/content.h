/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:16:42 by htsang            #+#    #+#             */
/*   Updated: 2023/06/24 11:00:54 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTENT_H
# define CONTENT_H

# include "LIBFT/vector.h"
# include "LIBFT/stringbuilder.h"
# include "MINISHELL/lexer.h"

typedef t_ft_vector	t_ast_redirection_vector;
typedef t_ft_vector	t_sb_vector;

struct s_ast_node_content
{
	t_ast_redirection_vector	redirection_in;
	t_ast_redirection_vector	redirection_out;
	t_sb_vector					assignment;
	t_sb_vector					command;
};

// TODO: interface for AST node content
int		ast_node_content_init(struct s_ast_node_content *content);
void	ast_node_content_free(struct s_ast_node_content *content);

// TODO: interface for vector
//vector free
void	free_io_redirect_vector(\
	t_ast_redirection_vector *io_redirect_vector);
void	free_sb_vector(t_sb_vector *sb_vector);
//vector utils
void	vector_copy_io_redirect(void	*buffer, void *io_redirect);
void	vector_copy_sb(void	*buffer, void *sb);

typedef enum e_ast_redirection_type
{
	REDIRCT_STDIN,
	REDIRECT_HEREDOC,
	REDIRECT_STDOUT,
	REDIRECT_STDOUT_APPEND
}	t_ast_redirection_type;

struct s_ast_redirection
{
	t_ast_redirection_type	type;
	t_ft_sb					content;
};

// TODO: interface for redirection (the struct)
int		ast_redirect_type_set(t_token_type token_type, \
	t_ast_redirection_type *io_file_type);
int		ast_node_str_set(t_ft_sb *content_str, const char *str, \
const size_t str_len);

#endif
