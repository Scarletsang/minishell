/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sawang <sawang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:02 by htsang            #+#    #+#             */
/*   Updated: 2023/06/27 15:41:35 by sawang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MINISHELL/execution/builtins.h"
#include <stdio.h>
#include "LIBFT/string.h"

//should builtin pwd use getcwd() or environment variable PWD?
// how large should the size be?
t_ms_exit_code	ms_execute_builtin_pwd(struct s_ms *ms, t_sb_vector *command)
{
	char	buf[PATH_MAX];
	char	*cwd;

	(void) command;
	(void) ms;
	cwd = getcwd(buf, PATH_MAX);
	if (!cwd)
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}

// int	main(void)
// {
// 	t_sb_vector				command;
// 	t_ft_sb					command0;
// 	char					*str;

// 	str = "pwd";
// 	ft_vector_init(&command, sizeof(t_ft_sb), 5, vector_copy_sb);
// 	ft_sb_init(&command0, 10);
// 	ft_sb_perform(&command0, ft_sb_action_append_len(str, ft_strlen(str)));
// 	ft_vector_append(&command, &command0);
// 	ms_builtin_pwd(NULL, &command, NULL);
// 	// free stuff
// 	return (0);
// }
