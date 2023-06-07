/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:05:03 by htsang            #+#    #+#             */
/*   Updated: 2023/06/07 20:51:55 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <termios.h>
#include <unistd.h>
// #include <stdlib.h>

// int main() {
//     struct termios  current_attr;

//     tcgetattr(STDIN_FILENO, &current_attr);
//     current_attr.c_lflag &= ~ICANON;
//     tcsetattr(STDIN_FILENO, TCSANOW, &current_attr);
//     return (EXIT_SUCCESS);
// }

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

void disableInterruptEcho() {
    struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("Failed to get terminal attributes");
        exit(EXIT_FAILURE);
    }
    term.c_cc[VINTR] = _POSIX_VDISABLE;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
        perror("Failed to set terminal attributes");
        exit(EXIT_FAILURE);
    }
}

void enableInterruptEcho() {
    struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("Failed to get terminal attributes");
        exit(EXIT_FAILURE);
    }
    term.c_cc[VINTR] = '\003';  // Restore the original interrupt character (Ctrl+C)
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
        perror("Failed to set terminal attributes");
        exit(EXIT_FAILURE);
    }
}

void disableEcho() {
    struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("Failed to get terminal attributes");
        exit(EXIT_FAILURE);
    }
	// term.c_cc[VINTR] = _POSIX_VDISABLE;
	term.c_lflag &= ~(ECHO | ICANON);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
        perror("Failed to set terminal attributes");
        exit(EXIT_FAILURE);
    }
}

int main() {
	char c;
	ssize_t	nread;
    disableEcho();

    // Your shell code here
	while ((nread = read(STDIN_FILENO, &c, 1)) != -1)
	{
		if (c == 3)
		{
			break;
		}
		write(STDOUT_FILENO, &c, 1);
	}
    return 0;
}
