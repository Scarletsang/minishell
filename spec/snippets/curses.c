/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curses.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:32:25 by htsang            #+#    #+#             */
/*   Updated: 2023/05/02 22:43:52 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char buf[1024];
    const char* term = getenv("TERM");

    if (term == NULL) {
        printf("TERM environment variable not set\n");
        return 1;
    }
    int ret = tgetent(buf, term);
    if (ret == -1) {
        printf("Could not open terminfo database\n");
        return 1;
    } else if (ret == 0) {
        printf("Terminal type \"%s\" not found in database\n", term);
        return 1;
    }
    printf("Terminal capabilities for %s:\n", term);
	tputs(tgetstr("cl", (char **) &buf), 1, putchar);
	tputs(tgetstr("cm", (char **) &buf), 1, putchar);
	tputs(tgetstr("ti", (char **) &buf), 1, putchar);
    // Use tgetstr(), tgetflag(), tgetnum() to retrieve terminal capabilities
    return 0;
}
