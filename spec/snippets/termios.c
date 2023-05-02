/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:05:03 by htsang            #+#    #+#             */
/*   Updated: 2023/05/02 22:11:43 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    struct termios  current_attr;

    tcgetattr(STDIN_FILENO, &current_attr);
    current_attr.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &current_attr);
    return (EXIT_SUCCESS);
}