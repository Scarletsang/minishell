/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 01:16:50 by htsang            #+#    #+#             */
/*   Updated: 2023/06/24 01:19:35 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_TESTER_H
# define PARSER_TESTER_H

# include <stdlib.h>
# include <stdio.h>
# include "MINISHELL/parser.h"

void	print_ast(struct s_ast_node *root);
void	print_ast_content(struct s_ast_node_content *content);
void	print_content_redirection(t_ast_redirection_vector *redirection);
void	print_content_sb_vector(t_sb_vector *sb_vector);

#endif