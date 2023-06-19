/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:24:47 by htsang            #+#    #+#             */
/*   Updated: 2023/06/07 18:49:20 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include "MINISHELL/execution/vars.h"

struct s_ms
{
	int					ipc[2];
	struct s_ms_vars	vars;
};

int		ms_init(struct s_ms *ms);

int		ms_free(struct s_ms *ms);

void	ms_ipc_send(struct s_ms *ms, char byte);

char	ms_ipc_receive(struct s_ms *ms);

#endif