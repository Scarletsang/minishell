#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>

void enableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void moveCursorUp(int n) {
    printf("\033[%dA", n);
}

void moveCursorDown(int n) {
    printf("\033[%dB", n);
}

void moveCursorRight(int n) {
    printf("\033[%dC", n);
}

void moveCursorLeft(int n) {
    printf("\033[%dD", n);
}

void setCursorPosition(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

int main() {
    enableRawMode();

    char	str[100];
	ssize_t nread;

    while ((nread = read(STDIN_FILENO, str, 100)) > 0) {
		str[nread] = 0;
		printf("%s", str);
		if (strcmp(str, "\033[A") == 0)
		{
			// printf("Up arrow key pressed\n");
			// moveCursorUp(1);
		}
		if (strcmp(str, "\033[B") == 0)
		{
			// printf("Down arrow key pressed\n");
			moveCursorDown(1);
		}
		if (strcmp(str, "\033[C") == 0)
		{
			// printf("Right arrow key pressed\n");
			moveCursorRight(1);
		}
		if (strcmp(str, "\033[D") == 0)
		{
			// printf("Left arrow key pressed\n");
			moveCursorLeft(1);
		}
		fflush(stdout);
    }

    return 0;
}