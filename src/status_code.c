/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 21:32:57 by htsang            #+#    #+#             */
/*   Updated: 2023/06/23 21:36:31 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/status_code.h"

enum e_ms_exit_code	ms_status_to_exit_code(t_ms_status status)
{
	if (status == PROGRAM_SUCCESS)
		return (EC_SUCCESS);
	return (EC_FAILURE);
}

enum e_ms_exit_code	ms_exit_code_from_signal(int signal)
{
	return (EC_SIGNAL_INTERRUPT_BASE + signal);
}
