#ifndef TESTS_H
# define TESTS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>

# define TSHELL_MAX_INPUT_SIZE 100

//////////////////////////////////////////////
/////////////      parser      ///////////////
//////////////////////////////////////////////

struct s_tparser
{
	void			**contents;
	const char		*line;
	unsigned int	content_capacity;
	unsigned int	content_size;
	unsigned int	read_index;
};

int		tparser_create(struct s_tparser *parser, unsigned int capacity);

int		tparser_resize(struct s_tparser *parser);

int		tparser_reset(struct s_tparser *parser, const char *line);

void	tparser_destroy(struct s_tparser *parser);

//////////////////////////////////////////////
///////////////  matchers   //////////////////
//////////////////////////////////////////////

int		tparser_match_int(struct s_tparser *parser, int n);

int		tparser_match_char(struct s_tparser *parser, char c);

int		tparser_match_string(struct s_tparser *parser, char *str);

//////////////////////////////////////////////
///////////////  consumers  //////////////////
//////////////////////////////////////////////

int		tparser_ignore_space(struct s_tparser *parser);

int		tparser_ignore_spaces(struct s_tparser *parser);

int		tparser_consume_int(struct s_tparser *parser);

int		tparser_consume_string(struct s_tparser *parser);

int		tparser_peek_digit(struct s_tparser *parser);

////////////////////////////////////////////////////////
/////////////     Consume parameters     ///////////////
////////////////////////////////////////////////////////

typedef enum	e_tshell_param_type
{
	TSHELL_INT,
	TSHELL_STRING,
}				t_tshell_param_type;

int		tparser_consume_by_type(struct s_tparser *tparser, \
t_tshell_param_type param_type);

int		tparser_consume_exactly_one_parameter(struct s_tparser *tparser, \
t_tshell_param_type param_type);

int		tparser_consume_one_parameter(struct s_tparser *tparser, \
t_tshell_param_type param_type);

int		tparser_consume_n_parameters(struct s_tparser *tparser, \
unsigned int param_amount, ...);

//////////////////////////////////////////////
///////////////   readers   //////////////////
//////////////////////////////////////////////

void	*tparser_read(struct s_tparser *parser);

//////////////////////////////////////////////
/////////////     interact     ///////////////
//////////////////////////////////////////////

typedef enum	e_tshell_status
{
	TSHELL_SUCCESS,
	TSHELL_FAILURE,
	TSHELL_EXIT,
}				t_tshell_status;

typedef	void			*(*t_init_func)(void);
typedef	t_tshell_status	(*t_program_func)(void *states, struct s_tparser *parser);
typedef	void			(*t_free_func)(void *states);

struct s_tshell
{
	const char		name[20];
	t_init_func		init;
	t_program_func	program;
	t_free_func		cleaner;
};

struct s_tshell_lines
{
	char	buffer[TSHELL_MAX_INPUT_SIZE];
	char	*current_line;
	size_t	current_line_size;
	size_t	previous_all_lines_sum_size;
	ssize_t	read_size;
};

void				interact(t_init_func init, t_program_func program, t_free_func cleaner);

/////////////////////////////////////////////////////
/////////////     Execute command     ///////////////
/////////////////////////////////////////////////////

typedef	void		(*t_printer_func)(void *states);

t_tshell_status		tshell_execute_printer(void *states, \
struct s_tparser *tparser, t_printer_func func);

#endif