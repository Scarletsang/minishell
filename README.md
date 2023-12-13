# Minishell

This is a shell written in C to mimic the basic functionality of BASH:

1. Piping commands
2. 4 types of redirection: '<', '<<', '>' and '>>'
3. builtins: cd, echo, env, exit, export, pwd and unset

## Design

The whole shell is written with the RAII philosophy from C++ in mind. Any `struct` always comes with a constructor and destructor. A constructor always includes words such as "init" or "create", they will allocate memory if they have to. A destructor always include words such as "free" or "destroy", they will free memory if constructor has allocated memory. If an object is reusable, a method called "reset" handle sanitizing the used object.

```c
// Data members of an object
struct s_example
{
	...
};

// Constructor
int		example_init(struct s_example *example); // or example_create

// Destructor
void	example_free(struct s_example *example); // or example_destroy

void	example_reset(struct s_example *example);

// methods to use the object
void	example_shout(struct s_example *example);
```

Each header represents one object in the program.

## Structure

### Persistent data

- global and environmental variables are stored in hashmaps

### Parser

- includes a lexer that tokenize the user input and pass it to the parser
- recursive descent parser that builds an abstract syntax tree according to the [grammer rules](docs/easy_grammar.bnf)

### Executor

- includes an expander that modifer the abstract syntax tree according to the variables stored when $ is detected
- Command piping logic and redirections
- Signals that corresponds to specific user input such as Ctrl+C