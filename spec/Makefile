################################
######     Variables     #######
################################

CC:=cc
CFLAGS:= -Wall -Wextra -Werror
ifdef FSANITIZE
	CFLAGS+= -g3 -fsanitize=address
	LDFLAGS+= -g3 -fsanitize=address
endif
SRC_DIR:=shells
INCLUDE_DIR= \
	include \
	../include \
	../lib/libft

###################################
######     Source files     #######
###################################

# To add souce files, create a varaible for each folder, and then
# contatenate them in the SRC variable like this:

MAIN_SRC:= $(shell find $(SRC_DIR) -name '*.c')
SRC:= $(MAIN_SRC)

####################################
######     Library files     #######
####################################

# To compile a library, store a variable for their library file like this
# and add a rule for it after the main rules:
# LIBRARY_NAME=lib/LIBRARY_NAME/LIBRARY_NAME.a
MINISHELL= $(CURDIR)/../libminishell.so
TSHELL= $(CURDIR)/tshell/libtshell.so

# To add a library, add the library header file like this:
# LIB_INCLUDE_DIR+= $(shell brew --prefix readline)/include

# Then add the library to the linking process in one of the following ways:
# LDFLAGS+= -Llib/LIBRARY_NAME -lLIBRARY_NAME
# LDFLAGS+= lib/LIBRARY_NAME/libLIBRARY_NAME.a
LDFLAGS+= -lminishell -L$(CURDIR)/.. -Wl,-rpath,$(CURDIR)/..
LDFLAGS+= -ltshell -L$(CURDIR)/tshell -Wl,-rpath,$(CURDIR)/tshell

###############################################
######     Executive names reformat     #######
###############################################

# This in effect makes all the object files to be compiled in the OBJ_DIR directory

SHELLS:= $(patsubst $(SRC_DIR)/%.c,%.shell.out,$(SRC))

#################################
######     Main rules     #######
#################################

all: DEPS
	@$(MAKE) $(SHELLS) -j

.SECONDEXPANSION:
%.shell.out: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(addprefix -iquote ,$(INCLUDE_DIR)) $(addprefix -I ,$(LIB_INCLUDE_DIR)) $< -o $@ $(LDFLAGS) && \
	echo "Compilation of $@ successful"

run:
ifdef WITH
	@DYLD_LIBRARY_PATH=$(CURDIR)/..:$(CURDIR)/tshell ./$(WITH).shell.out
else
	@DYLD_LIBRARY_PATH=$(CURDIR)/..:$(CURDIR)/tshell ./loader.shell.out
endif

##########################################
######     Library compilation     #######
##########################################

# To compile a library, add a rule like this:

DEPS: $(MINISHELL) $(TSHELL)

$(MINISHELL):
	@$(MAKE) $(if $(FSANITIZE),FSANITIZE=yes,) -C .. repack

$(TSHELL):
	@$(MAKE) $(if $(FSANITIZE),FSANITIZE=yes,) -C tshell re

# $(LIBRARY_NAME):
# 	@${MAKE} $(if $(FSANITIZE),FSANITIZE=yes,) -C lib/LIBRARY_NAME

###############################
######     Cleaning     #######
###############################

clean: 
	@$(MAKE) -C .. clean
	@$(MAKE) -C tshell clean

fclean: clean
	@$(MAKE) -C .. unpack
	@$(MAKE) -C tshell fclean
	@rm -f $(SHELLS)

re: fclean all

.PHONY: clean fclean re
