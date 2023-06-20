/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/06/20 21:45:51 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/execution/executor/builtins.h"
#include <stdio.h>

//should builtin pwd use getcwd() or environment variable PWD?
// how large should the size be?
int	ms_builtin_pwd(struct s_ms_executor *executor, t_sb_vector *command, \
struct s_ms *ms)
{
	long	size;
	char	*buf;
	char	*cwd;

	(void) executor;
	(void) command;
	(void) ms;
	size = 128;
	buf = malloc(sizeof(char) * size);
	if (!buf)
		return (EXIT_FAILURE);
	cwd = getcwd(buf, size);
	if (!cwd)
	{
		perror("pwd");
		free(buf);
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	free(buf);
	return (EXIT_SUCCESS);
}

// int	main(void)
// {
// 	t_sb_vector				command;
// 	t_ft_sb					command0;
// 	char					*str;

// 	str = "";
// 	ft_vector_init(&command, sizeof(t_ft_sb), 5, vector_copy_sb);
// 	ft_sb_init(&command0, 10);
// 	ft_sb_perform(&command0, ft_sb_action_append_len(str, 3));
// 	ft_vector_append(&command, &command0);
// 	ms_builtin_pwd(NULL, &command, NULL);
// 	// free stuff
// 	return (0);
// }
