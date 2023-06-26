################################
######     Variables     #######
################################

NAME:=minishell

CC:=cc
CFLAGS:= -Wall -Wextra -Werror
ifdef FSANITIZE
	CFLAGS+= -g3 -fsanitize=address
	LDFLAGS+= -g3 -fsanitize=address
endif
INCLUDE_DIR= \
	include \
	spec/parser

###################################
######     Source files     #######
###################################

# To add souce files, create a varaible for each folder, and then
# contatenate them in the SRC variable like this:
COMMON_SRC:=\
	status_code.c
LEXER_SRC:=\
	lexer/lexer.c \
	lexer/scanner_checker.c \
	lexer/scanner_maniputalor.c \
	lexer/token_maker.c \
	lexer/token_lst_utils.c \
	lexer/token_assignword_updater.c
PARSER_SRC:=\
	parser/node_content/ast_node_content.c \
	parser/node_content/content_vector.c \
	parser/node_content/content_vector_utils.c \
	parser/node_content/redirection.c \
	parser/ast/ast_node.c \
	parser/parser.c \
	parser/parser_cmd.c \
	parser/parser_cmd_prefix.c \
	parser/parser_cmd_suffix.c \
	parser/parser_complete_command.c \
	parser/parser_free.c \
	parser/parser_ioredirect.c \
	parser/parser_scanner_utils.c \
	parser/parser_tree_inserter.c
ERROR_PERINTER_SRC:=\
	error_printer/error_printer.c \
	error_printer/parser_error.c

VARS_SRC:=\
	execution/vars/vars.c \
	execution/vars/database.c \
	execution/vars/action.c
EXPANDER_SRC:=\
	execution/expander/expander.c \
	execution/expander/expander_dollar.c \
	execution/expander/match.c
PIPER_SRC:=\
	execution/piper/internal.c \
	execution/piper/piper.c \
	execution/piper/transmission.c
EXECUTOR_SRC:=\
	execution/executor/executor.c \
	execution/executor/action.c \
	execution/executor/heredoc.c \
	execution/executor/envp.c
BUILTINS_SRC:=\
	execution/builtins/echo.c \
	execution/builtins/cd.c \
	execution/builtins/export.c \
	execution/builtins/pwd.c \
	execution/builtins/unset.c \
	execution/builtins/env.c \
	execution/builtins/exit.c
EXECUTION_SRC:=\
	execution/execution.c \
	execution/pipe.c \
	execution/expansion.c \
	execution/builtin.c \
	execution/command.c \
	execution/command/assignment.c \
	execution/command/redirection.c \
	execution/command/executable.c
DEBUGGER_SRC:= \
	../spec/parser/parser_tester.c \
	../spec/parser/parser_tester_printer.c
MAIN_SRC:= \
	control/control.c \
	control/action.c \
	control/terminal.c \
	main.c

SRC:= $(COMMON_SRC) $(LEXER_SRC) $(PARSER_SRC) $(ERROR_PERINTER_SRC) $(VARS_SRC) $(EXPANDER_SRC) $(PIPER_SRC) $(EXECUTOR_SRC) $(BUILTINS_SRC) $(EXECUTION_SRC) $(DEBUGGER_SRC) $(MAIN_SRC)

####################################
######     Library files     #######
####################################

# To compile a library, store a variable for their library file like this
# and add a rule for it after the main rules:
LIBFT=lib/libft/libft.a

# To add a library, add the library header file like this:
LIB_INCLUDE_DIR+= lib/libft/include

# Then add the library to the linking process in one of the following ways:
# LDFLAGS+= -Llib/LIBRARY_NAME -lLIBRARY_NAME
# LDFLAGS+= lib/LIBRARY_NAME/libLIBRARY_NAME.a
LDFLAGS+= $(LIBFT)

# Specify the location of the binary and header file of the readline library
# on MacOS
ifeq ($(shell uname), Darwin)
	LIB_INCLUDE_DIR+= $(shell brew --prefix readline)/include
	LDFLAGS+= -lreadline -L$(shell brew --prefix readline)/lib
else
	LDFLAGS+= -lreadline
endif

###########################################
######     Object name reformat     #######
###########################################

# This in effect makes all the object files to be compiled in the OBJ_DIR directory

SRC_DIR:=src
OBJ_DIR:=obj
OBJ:= $(addprefix $(OBJ_DIR)/,$(subst /,@,$(SRC:.c=.o)))

#################################
######     Main rules     #######
#################################

all:
	@$(MAKE) $(NAME) -j

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) && echo "Compilation of $(NAME) successful"

bonus: re

##########################################
######     Library compilation     #######
##########################################

# To compile a library, add a rule like this:

# $(LIBRARY_NAME):
# 	@${MAKE} $(if $(FSANITIZE),FSANITIZE=yes,) -C lib/LIBRARY_NAME
$(LIBFT):
	@${MAKE} $(if $(FSANITIZE),FSANITIZE=yes,) USE="hashtable stringbuilder iostream" -C lib/libft

#########################################
######     Object compilation     #######
#########################################

.SECONDEXPANSION:
$(OBJ_DIR)/%.o: $(SRC_DIR)/$$(subst @,/,$$*).c
	@$(CC) $(CFLAGS) $(addprefix -iquote ,$(INCLUDE_DIR)) $(addprefix -I ,$(LIB_INCLUDE_DIR)) -c $< -o $@

$(OBJ): $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

#########################################################
######     install brew (for 42 evaluation)     #########
#########################################################

ifeq ($(shell uname), Darwin)
install_brew:
	@brew --version &>/dev/null && echo "brew already installed" || \
	( \
		( \
			mv $(HOME)/.brew $(HOME)/goinfre/.brew &>/dev/null || \
			rm -rf $(HOME)/.brew && rm -rf $(HOME)/goinfre/.brew \
		) && \
		git clone --depth=1 https://github.com/Homebrew/brew $(HOME)/goinfre/.brew && \
		brew --version &>/dev/null || \
		( \
			echo "export PATH=$HOME/goinfre/.brew/bin:$PATH" >> $(HOME)/.zshrc && \
			source $(HOME)/.zshrc \
		) && \
		echo "brew installed" \
	)

install_readline:
	@brew list readline &>/dev/null && echo "readline already installed" || \
	( \
		brew install readline && \
		echo "readline installed" \
	)
endif

###############################################
######     Pack objects for testing     #######
###############################################

pack: CFLAGS += -fPIC
pack: LDFLAGS += -shared
pack: $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) -o lib$(NAME).so $(LDFLAGS) && echo "Compilation of $(NAME).so successful"

unpack:
	@rm -f lib$(NAME).so

repack: unpack clean
	@$(MAKE) pack
###############################
######     Cleaning     #######
###############################

clean:
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) fclean -C lib/libft
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re bonus unpack repack
