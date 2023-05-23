// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   interact2.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/05/22 02:58:03 by anthonytsan       #+#    #+#             */
// /*   Updated: 2023/05/22 02:58:09 by anthonytsan      ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "tests.h"

// void	terminal_init(struct termios *term)
// {
//     tcgetattr(STDIN_FILENO, term);  // Get the current terminal attributes

//     // Disable canonical mode and echo to read input character by character
//     term->c_lflag &= ~(ICANON | ECHO);
//     tcsetattr(STDIN_FILENO, TCSANOW, term);
// }

// void	terminal_reset(struct termios *term)
// {
// 	term->c_lflag |= ICANON | ECHO;
//     tcsetattr(STDIN_FILENO, TCSANOW, term);

// }

// void	readline(char *buffer, unsigned int size)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (i < size && read(STDIN_FILENO, buffer + i, 1) > 0)
// 	{
// 		if (buffer[i] == '\n')
// 		{
// 			buffer[i] = 0;
// 			return ;
// 		}
// 		i++;
// 	}
	
// }

// void	interact(t_init_func init, t_program_func program, t_free_func cleaner)
// {
// 	struct termios		term;
// 	struct s_tparser	tparser;
// 	char				buffer[100];
// 	void				*states;
// 	char				*line_end;
// 	int					program_status;

// 	states = init();
// 	if (!states || tparser_create(&tparser, 10))
// 		return ;
// 	terminal_init(&term);
// 	printf("interactive shell> ");
// 	fflush(stdout);
// 	while (read(STDIN_FILENO, buffer, 1) > 0)
// 	{
// 		line_end = strrchr(buffer, '\n');
// 		if (!line_end)
// 		{
// 			printf("Line too long %s\n", buffer);
// 			continue;
// 		}
// 		*line_end = 0;
// 		if(strcmp(buffer, "exit") == 0)
// 			break;
// 		tparser_reset(&tparser, buffer);
// 		program_status = program(states, &tparser);
// 		if (program_status == -1)
// 			break;
// 		if(program_status)
// 			printf("Program error, received: %s\n", buffer);
// 		printf("interactive shell> ");
// 		fflush(stdout);
// 	}
// 	cleaner(states);
// 	tparser_destroy(&tparser);
// 	free(states);
// 	terminal_reset(&term);
// }
