/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tparser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 00:28:44 by htsang            #+#    #+#             */
/*   Updated: 2023/05/18 00:48:18 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

//////////////////////////////////////////////
/////////////      tparser      ///////////////
//////////////////////////////////////////////

int	tparser_create(struct s_tparser *tparser, unsigned int capacity, const char *line)
{
	tparser->contents = malloc(sizeof(char) * capacity);
	if (!tparser->contents)
		return (EXIT_FAILURE);
	tparser->line = line;
	tparser->content_size = capacity;
	tparser->read_index = 0;
	return (EXIT_SUCCESS);
}

int	tparser_resize(struct s_tparser *tparser)
{
	char	*new_contents;
	int		new_capacity;

	new_capacity = tparser->content_size * 2;
	new_contents = malloc(sizeof(char) * new_capacity);
	if (!new_contents)
		return (EXIT_FAILURE);
	ft_strlcpy(new_contents, tparser->contents, tparser->content_size);
	free(tparser->contents);
	tparser->contents = new_contents;
	tparser->content_size = new_capacity;
	return (EXIT_SUCCESS);
}

void	tparser_destroy(struct s_tparser *tparser)
{
	unsigned int	i;

	i = 0;
	while (i < tparser->content_size)
	{
		free(tparser->contents[i]);
		i++;
	}
	free(tparser->contents);
}

//////////////////////////////////////////////
///////////////  consumers  //////////////////
//////////////////////////////////////////////

int	tparser_ignore_space(struct s_tparser *tparser)
{
	if (tparser->line[tparser->read_index] == ' ')
	{
		tparser->read_index++;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	tparser_ignore_spaces(struct s_tparser *tparser)
{
	unsigned int	read_index;

	read_index = tparser->read_index;
	while (tparser->line[tparser->read_index] == ' ')
		tparser->read_index++;
	if (read_index == tparser->read_index)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
