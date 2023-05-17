#ifndef TESTS_H
# define TESTS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//////////////////////////////////////////////
/////////////      parser      ///////////////
//////////////////////////////////////////////

struct s_tparser
{
	void			**contents;
	const char		*line;
	unsigned int	content_size;
	unsigned int	read_index;
};

int		tparser_create(struct s_tparser *parser, unsigned int capacity, const char *line);

int		tparser_resize(struct s_tparser *parser);

void	tparser_destroy(struct s_tparser *parser);

//////////////////////////////////////////////
///////////////  consumers  //////////////////
//////////////////////////////////////////////

int		tparser_ignore_space(struct s_tparser *parser);

int		tparser_ignore_spaces(struct s_tparser *parser);

int		tparser_match_int(struct s_tparser *parser, int n);

int		tparser_match_int(struct s_tparser *parser, int n);

int		tparser_match_int(struct s_tparser *parser, int n);

int		tparser_consume_int(struct s_tparser *parser);

int		tparser_consume_char(struct s_tparser *parser);

int		tparser_consume_string(struct s_tparser *parser);

//////////////////////////////////////////////
///////////////   readers   //////////////////
//////////////////////////////////////////////

int		tparser_read_as_int(struct s_tparser *parser);

char	tparser_read_as_char(struct s_tparser *parser);

char	*tparser_read_as_string(struct s_tparser *parser);

void	*tparser_read(struct s_tparser *parser);

//////////////////////////////////////////////
/////////////     interact     ///////////////
//////////////////////////////////////////////

typedef	void	*(*t_init_func)(void);
typedef	int		(*t_program_func)(void *states, const char *line);
typedef	void	(*t_free_func)(void *states);

void		interact(t_init_func init, t_program_func program, t_free_func cleaner);

#endif