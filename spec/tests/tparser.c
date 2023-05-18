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
#include <stdarg.h>

//////////////////////////////////////////////
/////////////      tparser      ///////////////
//////////////////////////////////////////////

int	tparser_create(struct s_tparser *tparser, unsigned int capacity)
{
	tparser->contents = malloc(sizeof(void *) * capacity);
	if (!tparser->contents)
		return (EXIT_FAILURE);
	tparser->line = NULL;
	tparser->content_capacity = capacity;
	tparser->content_size = 0;
	tparser->read_index = 0;
	return (EXIT_SUCCESS);
}

int	tparser_resize(struct s_tparser *tparser)
{
	void			**new_contents;
	unsigned int	new_capacity;
	unsigned int	i;

	new_capacity = tparser->content_capacity * 2;
	new_contents = malloc(sizeof(void *) * new_capacity);
	if (!new_contents)
		return (EXIT_FAILURE);
	i = 0;
	while (i < tparser->content_size)
	{
		new_contents[i] = tparser->contents[i];
		i++;
	}
	free(tparser->contents);
	tparser->contents = new_contents;
	tparser->content_capacity = new_capacity;
	return (EXIT_SUCCESS);
}

int	tparser_reset(struct s_tparser *tparser, const char *line)
{
	unsigned int	i;

	i = 0;
	while (i < tparser->content_size)
	{
		free(tparser->contents[i]);
		i++;
	}
	tparser->line = line;
	tparser->content_size = 0;
	tparser->read_index = 0;
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
/////////////  matchers  /////////////////////
//////////////////////////////////////////////

static bool	tparser_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	tparser_match_int(struct s_tparser *tparser, int n)
{
	const char		*reset_line;
	const char		*int_end;
	const char		*int_start;

	reset_line = tparser->line;
	if ((n < 0) && tparser_match_char(tparser, '-'))
		return (EXIT_FAILURE);
	else
		tparser_match_char(tparser, '+');
	int_end = tparser->line;
	while (*int_end && tparser_is_digit(*int_end))
		int_end++;
	if (int_end == tparser->line)
	{
		tparser->line = reset_line;
		return (EXIT_FAILURE);
	}
	int_start = int_end - 1;
	while ((int_start != int_end) && (n > 0))
	{
		if (*int_start != (n % 10) + '0')
		{
			tparser->line = reset_line;
			return (EXIT_FAILURE);
		}
		n /= 10;
		int_start--;
	}
	tparser->line = int_end;
	return (EXIT_SUCCESS);
}

int	tparser_match_char(struct s_tparser *tparser, char c)
{
	if (c == 0)
	{
		if (*tparser->line)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (*tparser->line != c)
		return (EXIT_FAILURE);
	tparser->line++;
	return (EXIT_SUCCESS);
}

int	tparser_match_string(struct s_tparser *tparser, char *str)
{
	const char	*reset_line;

	reset_line = tparser->line;
	while (*tparser->line && *str)
	{
		if (*tparser->line != *str)
		{
			break ;
		}
		tparser->line++;
		str++;
	}
	if (*str)
	{
		tparser->line = reset_line;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//////////////////////////////////////////////
///////////////  consumers  //////////////////
//////////////////////////////////////////////

int	tparser_ignore_space(struct s_tparser *tparser)
{
	if (*tparser->line != ' ')
		return (EXIT_FAILURE);
	tparser->line++;
	return (EXIT_SUCCESS);
}

int	tparser_ignore_spaces(struct s_tparser *tparser)
{
	const char		*line;

	line = tparser->line;
	while (*line == ' ')
		line++;
	if (line == tparser->line)
		return (EXIT_FAILURE);
	tparser->line = line;
	return (EXIT_SUCCESS);
}

static bool	tparser_has_overflow(int n, int digit, int neg)
{
	if (neg > 0)
	{
		return (n > (INT_MAX / 10) - digit);
	}
	return (n > (INT_MIN / 10) + digit);
}

int	tparser_peek_digit(struct s_tparser *parser)
{
	if (!tparser_is_digit(*parser->line))
		return (-1);
	return (*parser->line - '0');
}

int	tparser_consume_int(struct s_tparser *tparser)
{
	const char	*reset_line;
	int			*content;
	int			n;
	int			digit;
	int			neg;

	reset_line = tparser->line;
	n = 0;
	neg = 1;
	if (tparser_match_char(tparser, '-'))
		neg = -1;
	else
		tparser_match_char(tparser, '+');
	digit = tparser_peek_digit(tparser);
	if (digit == -1)
	{
		tparser->line = reset_line;
		return (EXIT_FAILURE);
	}
	while (*tparser->line && (digit != -1))
	{
		n *= 10;
		n += digit;
		tparser->line++;
		digit = tparser_peek_digit(tparser);
		if (tparser_has_overflow(n, digit, neg))
		{
			printf("n: %d\n", n);
			tparser->line = reset_line;
			return (EXIT_FAILURE);
		}
	}
	if (tparser->content_size > tparser->content_capacity)
	{
		if (tparser_resize(tparser))
		{
			tparser->line = reset_line;
			return (EXIT_FAILURE);
		}
	}
	content = malloc(sizeof(int));
	if (!content)
	{
		tparser->line = reset_line;
		return (EXIT_FAILURE);
	}
	*content = n * neg;
	tparser->contents[tparser->content_size] = content;
	tparser->content_size++;
	return (EXIT_SUCCESS);
}

int		tparser_consume_string(struct s_tparser *parser)
{
	const char	*reset_line;
	char		*content;
	int			i;

	reset_line = parser->line;
	i = 0;
	while (parser->line[i] && parser->line[i] != ' ')
		i++;
	if (parser->content_size > parser->content_capacity)
	{
		if (tparser_resize(parser))
		{
			parser->line = reset_line;
			return (EXIT_FAILURE);
		}
	}
	content = malloc(sizeof(char) * (i + 1));
	if (!content)
	{
		parser->line = reset_line;
		return (EXIT_FAILURE);
	}
	strlcpy(content, parser->line, i + 1);
	parser->contents[parser->content_size] = content;
	parser->content_size++;
	parser->line += i;
	return (EXIT_SUCCESS);
}

////////////////////////////////////////////////////////
/////////////     Consume parameters     ///////////////
////////////////////////////////////////////////////////

int	tparser_consume_by_type(struct s_tparser *tparser, \
t_tshell_param_type param_type)
{
	if (param_type == TSHELL_INT)
	{
		if (tparser_consume_int(tparser))
			return (EXIT_FAILURE);
	}
	else if (param_type == TSHELL_STRING)
	{
		if (tparser_consume_string(tparser))
			return (EXIT_FAILURE);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	tparser_consume_exactly_one_parameter(struct s_tparser *tparser, \
t_tshell_param_type param_type)
{
	if (tparser_consume_one_parameter(tparser, param_type))
		return (EXIT_FAILURE);
	tparser_ignore_spaces(tparser);
	if (tparser_match_char(tparser, '\0'))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	tparser_consume_one_parameter(struct s_tparser *tparser, \
t_tshell_param_type param_type)
{
	tparser_ignore_spaces(tparser);
	if (tparser_consume_by_type(tparser, param_type))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	tparser_consume_n_parameters(struct s_tparser *tparser, \
unsigned int param_amount, ...)
{
	va_list	param_arr;
	int		param_type;

	va_start(param_arr, param_amount);
	tparser_ignore_spaces(tparser);
	while (param_amount > 0)
	{
		param_type = (int) va_arg(param_arr, int);
		if (tparser_consume_by_type(tparser, param_type))
		{
			va_end(param_arr);
			return (EXIT_FAILURE);
		}
		tparser_ignore_spaces(tparser);
		param_amount--;
	}
	va_end(param_arr);
	return (EXIT_SUCCESS);
}

//////////////////////////////////////////////
///////////////   readers   //////////////////
//////////////////////////////////////////////

void	*tparser_read(struct s_tparser *parser)
{
	void	*content;

	if (parser->read_index > parser->content_size)
		return (NULL);
	content = parser->contents[parser->read_index];
	parser->read_index++;
	return (content);
}
