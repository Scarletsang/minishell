/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/06/28 11:04:09 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/execution/command/builtins.h"
#include <stdio.h>

//should builtin pwd use getcwd() or environment variable PWD?
// how large should the size be?
t_ms_exit_code	ms_execute_builtin_pwd(struct s_ms *ms, t_sb_vector *command)
{
	long	size;
	char	*buf;
	char	*cwd;

	(void) command;
	(void) ms;
	size = 128;
	buf = malloc(sizeof(char) * size);
	if (!buf)
		return (EC_FAILURE);
	cwd = getcwd(buf, size);
	if (!cwd)
	{
		perror("pwd");
		free(buf);
		return (EC_FAILURE);
	}
	printf("%s\n", cwd);
	free(buf);
	return (EC_SUCCESS);
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
