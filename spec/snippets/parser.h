# include "MINISHELL/vector.h"

struct s_AST_selection
{
	const char	*start;
	size_t		length;
};

enum	e_AST_redirection_type
{
	REDIRECT_STDIN,
	REDIRECT_STDIN_HEREDOC,
	REDIRECT_STDOUT,
	REDIRECT_STDOUT_APPEND,
};

struct s_AST_redirection
{
	enum e_AST_redirection_type	type;
	struct s_AST_redirection	selection;
};

// vector of t_AST_redirection
typedef t_vector	t_AST_redirect_queue;

// vector of t_AST_selection
typedef t_vector	t_AST_assignment_vector;

// vector of t_AST_selection
typedef t_vector	t_AST_command_vector;

struct s_AST_content
{
	t_AST_redirect_queue	stdin;
	t_AST_redirect_queue	stdout;
	t_AST_assignment_vector	assignments;
	t_AST_command_vector	command;			
};

struct s_AST
{
	struct s_AST_content	*content;
	struct s_AST			*left;
	struct s_AST			*right;
};

struct s_parser
{
	struct s_AST	*root;
	struct s_AST	*current;
};