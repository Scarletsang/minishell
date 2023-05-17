/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder_shell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:45:26 by htsang            #+#    #+#             */
/*   Updated: 2023/05/18 00:28:19 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "stringbuilder_test.h"

struct s_sb	*stringbuilder_shell_init(void)
{
	struct s_sb	*sb;

	sb = malloc(sizeof(struct s_sb));
	if (sb_create(sb, 20))
	{
		free(sb);
		return (NULL);
	}
	return (sb);
}

int	stringbuilder_shell(struct s_sb *ht, const char *line)
{
	char	*arguments[2];

	if (ft_strcmp(line, "print") == 0)
	{
		ht_print(ht);
		return (EXIT_SUCCESS);
	}
	else if (ft_strcmp(line, "add") == ' ')
	{
		line += 4;
		arguments[0] = consume_one(&line);
		line++;
		arguments[1] = consume_one(&line);
		if (!arguments[0] || !arguments[1])
		{
			free_arguments(arguments);
			return (EXIT_FAILURE);
		}
		if (ht_add(ht, arguments[0], arguments[1]))
			return (EXIT_FAILURE);
		ht_print(ht);
		return (EXIT_SUCCESS);
	}
	else if (ft_strcmp(line, "update") == ' ')
	{
		line += 7;
		arguments[0] = consume_one(&line);
		line++;
		arguments[1] = consume_one(&line);
		if (!arguments[0] || !arguments[1])
		{
			free_arguments(arguments);
			return (EXIT_FAILURE);
		}
		if (ht_update(ht, arguments[0], arguments[1]))
			return (EXIT_FAILURE);
		ht_print(ht);
		return (EXIT_SUCCESS);
	}
	else if (ft_strcmp(line, "get") == ' ')
	{
		line += 4;
		arguments[0] = consume_one(&line);
		if (!arguments[0])
			return (EXIT_FAILURE);
		printf("got: %s\n", (char *) ht_get(ht, arguments[0]));
		return (EXIT_SUCCESS);
	}
	else if (ft_strcmp(line, "del") == ' ')
	{
		line += 4;
		arguments[0] = consume_one(&line);
		if (!arguments[0])
			return (EXIT_FAILURE);
		ht_del(ht, arguments[0]);
		ht_print(ht);
		return (EXIT_SUCCESS);
	}
	
	return (0);
}
