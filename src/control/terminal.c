/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:20:47 by htsang            #+#    #+#             */
/*   Updated: 2023/06/26 02:52:10 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "MINISHELL/minishell.h"

int	ms_terminal_settings_change(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (EXIT_FAILURE);
	term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ms_terminal_settings_restore(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (EXIT_FAILURE);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
