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
	lib/libft/include

###################################
######     Source files     #######
###################################

# To add souce files, create a varaible for each folder, and then
# contatenate them in the SRC variable like this:

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
	execution/execution.c \
	execution/executor/executor.c \
	execution/executor/action.c \
	execution/executor/envp.c \
	execution/executor/enactment/enactment.c \
	execution/executor/enactment/expand_node.c \
	execution/executor/enactment/node.c \
	execution/executor/enactment/redirection.c \
	execution/executor/builtins/builtins.c
MAIN_SRC:= \
	main.c
SRC:= $(VARS_SRC) $(EXPANDER_SRC) $(PIPER_SRC) $(EXECUTOR_SRC) $(MAIN_SRC)

####################################
######     Library files     #######
####################################

# To compile a library, store a variable for their library file like this
# and add a rule for it after the main rules:
LIBFT=lib/libft/libft.a

# To add a library, add the library header file like this:
LIB_INCLUDE_DIR+= lib/libft

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
	@${MAKE} $(if $(FSANITIZE),FSANITIZE=yes,) -C lib/libft

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
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re bonus unpack repack