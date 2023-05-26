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
	include

###################################
######     Source files     #######
###################################

# To add souce files, create a varaible for each folder, and then
# contatenate them in the SRC variable like this:

VECTOR_SRC:= \
	vector/vector.c \
	vector/buffer.c \
	vector/setters.c \
	vector/action.c
HASHTABLE_SRC:= \
	hashtable/hashtable.c \
	hashtable/mutation.c \
	hashtable/printer.c \
	hashtable/getters.c \
	hashtable/entry.c \
	hashtable/hash/hash.c \
	hashtable/hash/rehash.c
STRINGBUILDER_SRC:= \
	stringbuilder/stringbuilder.c \
	stringbuilder/search.c \
	stringbuilder/action/action.c \
	stringbuilder/action/delete.c \
	stringbuilder/action/insert.c \
	stringbuilder/action/field_validator.c
VARS_SRC:=\
	execution/vars/vars.c \
	execution/vars/database.c \
	execution/vars/action.c
MAIN_SRC:= \
	main.c
SRC:= $(VECTOR_SRC) $(HASHTABLE_SRC) $(STRINGBUILDER_SRC) $(VARS_SRC) $(MAIN_SRC)

####################################
######     Library files     #######
####################################

# To compile a library, store a variable for their library file like this
# and add a rule for it after the main rules:
LIBFT=lib/libft/libft.a

# To add a library, add the library header file like this:
LIB_INCLUDE_DIR+= $(shell brew --prefix readline)/include
LIB_INCLUDE_DIR+= lib/libft

# Then add the library to the linking process in one of the following ways:
# LDFLAGS+= -Llib/LIBRARY_NAME -lLIBRARY_NAME
# LDFLAGS+= lib/LIBRARY_NAME/libLIBRARY_NAME.a
LDFLAGS+= -lreadline -L $(shell brew --prefix readline)/lib/
LDFLAGS+= $(LIBFT)

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
	@$(CC) $(OBJ) -o lib$(NAME).dylib $(LDFLAGS) && echo "Compilation of $(NAME).dylib successful"

unpack:
	@rm -f lib$(NAME).dylib

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

.PHONY: clean fclean re bonus paco unpack repack