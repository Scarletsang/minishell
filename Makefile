################################
######     Variables     #######
################################

NAME:=minishell

CC:=cc
CFLAGS= -Wall -Wextra -Werror
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

MAIN_SRC:= \
	main.c
SRC:= $(MAIN_SRC)

####################################
######     Library files     #######
####################################

# To compile a library, store a variable for their library file like this
# and add a rule for it after the main rules:
# LIBRARY_NAME=lib/LIBRARY_NAME/LIBRARY_NAME.a

# To add a library, add the library header file like this:
# INCLUDE_DIR+= lib/LIBRARY_NAME/include

# Then add the library to the linking process in one of the following ways:
# LDFLAGS+= -Llib/LIBRARY_NAME -lLIBRARY_NAME
# LDFLAGS+= lib/LIBRARY_NAME/libLIBRARY_NAME.a
LDFLAGS += -lreadline

###########################################
######     Object name reformat     #######
###########################################

# This in effect makes all the object files to be compiled in the OBJ_DIR directory

SRC_DIR:=src
OBJ_DIR:=obj
OBJ:=$(addprefix $(OBJ_DIR)/,$(subst /,@,$(SRC:.c=.o)))

#################################
######     Main rules     #######
#################################

all:
	@$(MAKE) $(NAME) -j

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) && echo "Compilation of $(NAME) successful"

bonus: re

##########################################
######     Library compilation     #######
##########################################

# To compile a library, add a rule like this:

# $(LIBRARY_NAME):
# 	@${MAKE} $(if $(FSANITIZE),FSANITIZE=yes,) -C lib/LIBRARY_NAME

#########################################
######     Object compilation     #######
#########################################

.SECONDEXPANSION:
$(OBJ_DIR)/%.o: $(SRC_DIR)/$$(subst @,/,$$*).c
	@$(CC) $(CFLAGS) $(addprefix -iquote ,$(INCLUDE_DIR)) -c $< -o $@

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

###############################
######     Cleaning     #######
###############################

clean: 
	@rm -f $(OBJS)

fclean: clean
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re bonus