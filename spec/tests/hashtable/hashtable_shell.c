/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:45:26 by htsang            #+#    #+#             */
/*   Updated: 2023/05/18 00:22:33 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "hashtable_test.h"

struct s_ht	*hashtable_shell_init(void)
{
	struct s_ht	*ht;

	ht = malloc(sizeof(struct s_ht));
	if (ht_create(ht, 20))
	{
		free(ht);
		return (NULL);
	}
	return (ht);
}

char	*consume_one(const char **line)
{
	const char		*copy;
	unsigned int	len;
	char			*result;

	copy = *line;
	len = 0;
	while (*copy && *copy != ' ')
	{
		len++;
		copy++;
	}
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, *line, len + 1);
	*line += len;
	return (result);
}

void	free_arguments(char *arguments[2])
{
	if(arguments[0])
		free(arguments[0]);
	if(arguments[1])
		free(arguments[1]);
}

int	hashtable_shell(struct s_ht *ht, const char *line)
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
