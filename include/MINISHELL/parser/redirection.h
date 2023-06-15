/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:16:42 by htsang            #+#    #+#             */
/*   Updated: 2023/06/15 19:33:09 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

#include "MINISHELL/vector.h"
#include "MINISHELL/stringbuilder.h"

typedef t_vector	t_ast_redirection_vector;

// TODO: interface for redirection vector

// handle < redirection (stdin)
// handle << heredoc
// handle > redirection (stdout)
// handle >> redirection appends (stdout)
enum e_ast_redirection_type
{
	REDIRCT_STDIN,
	REDIRECT_HEREDOC,
	REDIRECT_STDOUT,
	REDIRECT_STDOUT_APPEND
};

struct s_ast_redirection
{
	enum e_ast_redirection_type	type;
	t_sb						content;
};

// TODO: interface for redirection (the struct)

#endif
